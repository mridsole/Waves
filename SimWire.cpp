#include "stdafx.h"
#include "SimWire.h"
#include "SimNode.h"

#include "SimGraphInterface.h"

#include <algorithm>
#include <cmath>
#include <assert.h>

#include <stdio.h>

using namespace hwsim;

SimWire::SimWire():
	edge(nullptr),
	_isInitialized(false), 
	_isConfigValid(false) {

	
}

SimWire::SimWire(const Config& config) :
	edge(nullptr),
	_isInitialized(false),
	_isConfigValid(false) {
	
	this->setConfig(config);
}

SimWire::~SimWire() {

}

void SimWire::update(float dt) {

	// assuming we updated temporal index last time
	// get the indices
	unsigned int current_idx = this->_currentTimestepIndex;
	unsigned int next_idx = (current_idx + 1) % this->_config.storeTimesteps;
	unsigned int previous_idx = (this->_config.storeTimesteps + current_idx - 1) %
		this->_config.storeTimesteps;

	// compute derivatives
	this->_computeWaveDerivatives(dt);
	this->_computeHeatDerivatives(dt);

	// nice reference aliases for the current derivative vectors
	auto& wave =	this->_wave[current_idx];
	auto& wave_x =	this->_wave_x[current_idx];
	auto& wave_xx = this->_wave_xx[current_idx];
	auto& wave_t =	this->_wave_t[current_idx];
	auto& heat =	this->_heat[current_idx];
	auto& heat_x =	this->_heat_x[current_idx];
	auto& heat_xx = this->_heat_xx[current_idx];

	auto& wave_previous = this->_wave[previous_idx];

	// what we need to change
	auto& wave_next = this->_wave[next_idx];
	auto& heat_next = this->_heat[next_idx];

	// update the non-boundary wave bits
	float wave_tt;
	for (unsigned i = 1; i < this->_config.nx - 1; i++) {

		wave_tt = std::pow(this->_waveSpeed[i], 2) * wave_xx[i - 1] - 
			this->_damping[i] * wave_t[i];

		wave_next[i] = std::pow(dt, 2) * wave_tt + 2 * wave[i] - wave_previous[i];
	}

	// we should store the 'energy lost' differential due to damping
	// so we can turn it into heat -> conserve energy

	// update the non-boundary heat bits
	for (unsigned int i = 1; i < this->_config.nx - 1; i++) {

		heat_next[i] = dt * this->_diffusivity[i] * heat_xx[i - 1] + heat[i];
	}

	// update the wave boundaries - trusting that our node pointers aren't null!
	_updateWaveBoundaries(wave_next, dt);

	// update the heat boundaries
	_updateHeatBoundaries(heat_next, dt);

	// update temporal index for the next cycle
	this->_updateTemporalIndex();
}

bool SimWire::initialize(const Config& config, const InitState& initState, float dt) {

	// config set + validate
	if (!this->setConfig(config))
		return false;

	// refs to builders
	const auto& initWave = *initState.initWave.get();
	const auto& initWaveVelocity = *initState.initWaveVelocity.get();
	const auto& initHeat = *initState.initHeat.get();
	const auto& waveSpeed = *initState.waveSpeed.get();
	const auto& damping	= *initState.damping.get();
	const auto& diffusivity = *initState.diffusivity.get();

	// start storing stuff
	this->_config.nx = config.nx;
	this->_config.storeTimesteps = config.storeTimesteps;
	this->_config.dx = config.dx;

	// now we can just construct directly from the state builders
	//this->_waveSpeed = waveSpeed(this->_config.nx);
	//this->_damping = damping(this->_config.nx);
	//this->_diffusivity = diffusivity(this->_config.nx);

	// wave magnitude
	//this->_wave.resize(this->_config.storeTimesteps);
	//for (unsigned i = 0; i < this->_wave.size(); i++)
	//	this->_wave[i] = initWave(this->_config.nx);

	//// heat magnitude
	//this->_heat.resize(this->_config.storeTimesteps);
	//for (unsigned i = 0; i < this->_heat.size(); i++)
	//	this->_heat[i] = initHeat(this->_config.nx);

	//// wave magnitude time derivative
	//this->_wave_t.resize(this->_config.storeTimesteps);
	//for (unsigned i = 0; i < this->_wave_t.size(); i++) {
	//	this->_wave_t[i].resize(this->_config.nx);
	//}

	// wave magnitude space derivative
	this->_wave_x.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave_x.size(); i++) {
		this->_wave_x[i].resize(this->_config.nx - 1);
	}

	// second wave magnitude space derivative
	this->_wave_xx.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave_xx.size(); i++) {
		this->_wave_xx[i].resize(this->_config.nx - 2);
	}

	// heat magnitude space derivative
	this->_heat_x.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_heat_x.size(); i++) {
		this->_heat_x[i].resize(this->_config.nx - 1);
	}

	// second heat magnitude space derivative
	this->_heat_xx.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_heat_xx.size(); i++) {
		this->_heat_xx[i].resize(this->_config.nx - 2);
	}

	// reset circular buffer position
	this->_currentTimestepIndex = 0;

	// set the given initial state
	auto& _wave_current = this->_wave[this->_currentTimestepIndex];
	auto& _heat_current = this->_heat[this->_currentTimestepIndex];
	auto& _wave_next = this->_wave[(this->_currentTimestepIndex + 1) % this->_config.storeTimesteps];
	auto& _heat_next = this->_heat[(this->_currentTimestepIndex + 1) % this->_config.storeTimesteps];

	for (unsigned i = 0; i < this->_config.nx; i++) {

		// set initial wave and heat state
		//_wave_current[i] = initWave[i];
		//_heat_current[i] = initHeat[i];

		// use velocity information to fill the next timestep
		//_wave_next[i] = initWave[i] + initWaveVelocity[i] * dt;

		// this isn't really valid - but just set the next heat step
		// to the current heat step (we have to do this because at this 
		// point in time we don't have boundary condition info)
		_heat_next[i] = _heat_current[i];
	}

	// might as well compute some derivatives while we're here
	this->_computeWaveDerivatives(dt);
	this->_computeHeatDerivatives(dt);

	// update the wave boundaries - trusting that our node pointers aren't null!
	_updateWaveBoundaries(_wave_next, dt);

	// update the heat boundaries
	_updateHeatBoundaries(_heat_next, dt);

	// update indices
	this->_updateTemporalIndex();

	// we're done!
	this->_isInitialized = true;

	return true;
}

// hnnng
bool SimWire::initialize(const Config& config,
	std::vector<float>& initWave,
	std::vector<float>& initWaveVelocity, 
	std::vector<float>& initHeat, 
	std::vector<float>& waveSpeed,
	std::vector<float>& damping, 
	std::vector<float>& diffusivity,
	float dt) {

	// config set + validate
	if (!this->setConfig(config)) {

		// config not valid -> don't initialize
		return false;
	}

	// check the dimensions of everything
	assert(this->_config.nx == initWave.size());
	assert(this->_config.nx == initWaveVelocity.size());
	assert(this->_config.nx == initHeat.size());

	// check dimensions of wire properties
	assert(this->_config.nx == waveSpeed.size());
	assert(this->_config.nx == damping.size());
	assert(this->_config.nx == diffusivity.size());

	// values look okay, start storing stuff
	this->_config.nx = config.nx;
	this->_config.storeTimesteps = config.storeTimesteps;
	this->_config.dx = config.dx;

	// resize wire property storage and store the new stuff
	this->_waveSpeed.resize(this->_config.nx);
	this->_damping.resize(this->_config.nx);
	this->_diffusivity.resize(this->_config.nx);

	for (unsigned i = 0; i < this->_config.nx; i++) {

		this->_waveSpeed[i] = waveSpeed[i];
		this->_damping[i] = damping[i];
		this->_diffusivity[i] = diffusivity[i];
	}

	// resize internal storage

	// wave magnitude
	this->_wave.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave.size(); i++) {
		this->_wave[i].resize(this->_config.nx);
	}

	// heat magnitude
	this->_heat.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_heat.size(); i++) {
		this->_heat[i].resize(this->_config.nx);
	}

	// wave magnitude time derivative
	this->_wave_t.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave_t.size(); i++) {
		this->_wave_t[i].resize(this->_config.nx);
	}

	// wave magnitude space derivative
	this->_wave_x.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave_x.size(); i++) {
		this->_wave_x[i].resize(this->_config.nx - 1);
	}

	// second wave magnitude space derivative
	this->_wave_xx.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave_xx.size(); i++) {
		this->_wave_xx[i].resize(this->_config.nx - 2);
	}

	// heat magnitude space derivative
	this->_heat_x.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_heat_x.size(); i++) {
		this->_heat_x[i].resize(this->_config.nx - 1);
	}

	// second heat magnitude space derivative
	this->_heat_xx.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_heat_xx.size(); i++) {
		this->_heat_xx[i].resize(this->_config.nx - 2);
	}

	// reset circular buffer position
	this->_currentTimestepIndex = 0;

	// set the given initial state
	auto& _wave_current = this->_wave[this->_currentTimestepIndex];
	auto& _heat_current = this->_heat[this->_currentTimestepIndex];
	auto& _wave_next = this->_wave[(this->_currentTimestepIndex + 1) % this->_config.storeTimesteps];
	auto& _heat_next = this->_heat[(this->_currentTimestepIndex + 1) % this->_config.storeTimesteps];

	for (unsigned i = 0; i < this->_config.nx; i++) {

		// set initial wave and heat state
		_wave_current[i] = initWave[i];
		_heat_current[i] = initHeat[i];
		
		// use velocity information to fill the next timestep
		_wave_next[i] = initWave[i] + initWaveVelocity[i] * dt;

		// this isn't really valid - but just set the next heat step
		// to the current heat step (we have to do this because at this 
		// point in time we don't have boundary condition info)
		_heat_next[i] = _heat_current[i];
	}

	// might as well compute some derivatives while we're here
	this->_computeWaveDerivatives(dt);
	this->_computeHeatDerivatives(dt);

	// update the wave boundaries - trusting that our node pointers aren't null!
	_updateWaveBoundaries(_wave_next, dt);

	// update the heat boundaries
	_updateHeatBoundaries(_heat_next, dt);

	// update indices
	this->_updateTemporalIndex();

	// we're done!
	this->_isInitialized = true;

	return true;
}

bool SimWire::initialize(std::vector<float>& initWave,
	std::vector<float>& initWaveVelocity,
	std::vector<float>& initHeat,
	std::vector<float>& waveSpeed,
	std::vector<float>& damping,
	std::vector<float>& diffusivity,
	float dt) {

	// make sure we actually have a valid configuration first
	if (!this->_isConfigValid) {
		return false;
	}

	// some more checks - just asserts for now as these really should not happen
	// check the dimensions of everything
	assert(this->_config.nx == initWave.size());
	assert(this->_config.nx == initWaveVelocity.size());
	assert(this->_config.nx == initHeat.size());

	// check dimensions of wire properties
	assert(this->_config.nx == waveSpeed.size());
	assert(this->_config.nx == damping.size());
	assert(this->_config.nx == diffusivity.size());

	// resize wire property storage and store the new stuff
	this->_waveSpeed.resize(this->_config.nx);
	this->_damping.resize(this->_config.nx);
	this->_diffusivity.resize(this->_config.nx);

	for (unsigned i = 0; i < this->_config.nx; i++) {

		this->_waveSpeed[i] = waveSpeed[i];
		this->_damping[i] = damping[i];
		this->_diffusivity[i] = diffusivity[i];
	}

	// resize internal storage

	// wave magnitude
	this->_wave.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave.size(); i++) {
		this->_wave[i].resize(this->_config.nx);
	}

	// heat magnitude
	this->_heat.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_heat.size(); i++) {
		this->_heat[i].resize(this->_config.nx);
	}

	// wave magnitude time derivative
	this->_wave_t.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave_t.size(); i++) {
		this->_wave_t[i].resize(this->_config.nx);
	}

	// wave magnitude space derivative
	this->_wave_x.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave_x.size(); i++) {
		this->_wave_x[i].resize(this->_config.nx - 1);
	}

	// second wave magnitude space derivative
	this->_wave_xx.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_wave_xx.size(); i++) {
		this->_wave_xx[i].resize(this->_config.nx - 2);
	}

	// heat magnitude space derivative
	this->_heat_x.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_heat_x.size(); i++) {
		this->_heat_x[i].resize(this->_config.nx - 1);
	}

	// second heat magnitude space derivative
	this->_heat_xx.resize(this->_config.storeTimesteps);
	for (unsigned i = 0; i < this->_heat_xx.size(); i++) {
		this->_heat_xx[i].resize(this->_config.nx - 2);
	}

	// reset circular buffer position
	this->_currentTimestepIndex = 0;

	// set the given initial state
	auto& _wave_current = this->_wave[this->_currentTimestepIndex];
	auto& _heat_current = this->_heat[this->_currentTimestepIndex];
	auto& _wave_next = this->_wave[(this->_currentTimestepIndex + 1) % this->_config.storeTimesteps];
	auto& _heat_next = this->_heat[(this->_currentTimestepIndex + 1) % this->_config.storeTimesteps];

	for (unsigned i = 0; i < this->_config.nx; i++) {

		// set initial wave and heat state
		_wave_current[i] = initWave[i];
		_heat_current[i] = initHeat[i];

		// use velocity information to fill the next timestep
		_wave_next[i] = initWave[i] + initWaveVelocity[i] * dt;

		// this isn't really valid - but just set the next heat step
		// to the current heat step (we have to do this because at this 
		// point in time we don't have boundary condition info)
		_heat_next[i] = _heat_current[i];
	}

	// might as well compute some derivatives while we're here
	this->_computeWaveDerivatives(dt);
	this->_computeHeatDerivatives(dt);

	// update the wave boundaries - trusting that our node pointers aren't null!
	_updateWaveBoundaries(_wave_next, dt);

	// update the heat boundaries
	_updateHeatBoundaries(_heat_next, dt);

	// update indices
	this->_updateTemporalIndex();

	// we're done!
	this->_isInitialized = true;

	return true;
}

const std::vector<float>& SimWire::getWave() const {

	return this->_wave[this->_currentTimestepIndex];
}

const std::vector<float>& SimWire::getHeat() const {
	
	return this->_heat[this->_currentTimestepIndex];
}

const std::vector<float>& SimWire::getWavePast(unsigned int n) const {

	assert(n < this->_config.storeTimesteps);

	return this->_wave[(this->_currentTimestepIndex + n) % this->_config.storeTimesteps];
}

const std::vector<float>& SimWire::getHeatPast(unsigned int n) const {

	assert(n < this->_config.storeTimesteps);

	return this->_heat[(this->_currentTimestepIndex + n) % this->_config.storeTimesteps];
}

const std::vector<float>& SimWire::getWaveFuture() const {

	unsigned int next_idx = (this->_currentTimestepIndex + 1) % this->_config.storeTimesteps;

	return this->_wave[next_idx];
}

const std::vector<float>& SimWire::getHeatFuture() const {

	unsigned int next_idx = (this->_currentTimestepIndex + 1) % this->_config.storeTimesteps;

	return this->_heat[next_idx];
}

void SimWire::setStoreTimesteps(unsigned int storeTimesteps) {

	if (storeTimesteps < 3) {
		this->_config.storeTimesteps = 3;
	} else {
		this->_config.storeTimesteps = storeTimesteps;
	}
}

unsigned int SimWire::getStoreTimesteps() const {
	
	return this->_config.storeTimesteps;
}

bool SimWire::setConfig(const Config& config) {

	// validation checks first
	if (config.dx > 0.f &&
		config.nx >= 4 &&
		config.storeTimesteps >= 3) {

		// valid -> store data
		this->_config = config;
		this->_isConfigValid = true;

		return true;
	} else {

		return false;
	}
}

const SimWire::Config& SimWire::getConfig() const {

	return this->_config;
}

bool SimWire::isConfigValid() const {

	return this->_isConfigValid;
}

bool SimWire::isInitialized() const {

	// TODO: do initialization checks here
	// don't just return _isInitialized!

	return this->_isInitialized;
}

void SimWire::_computeWaveDerivatives(float dt) {

	// first work out the indices
	unsigned int current_idx = this->_currentTimestepIndex;
	unsigned int previous_idx = (this->_config.storeTimesteps + current_idx - 1) %
		this->_config.storeTimesteps;

	auto& _wave_current = this->_wave[current_idx];

	// first wave spatial derivative
	auto& _wave_x_current = this->_wave_x[current_idx];

	for (unsigned i = 0; i < this->_config.nx - 1; i++) {
		_wave_x_current[i] = (_wave_current[i + 1] - _wave_current[i]) / this->_config.dx;
	}

	// second wave spatial derivative
	auto& _wave_xx_current = this->_wave_xx[current_idx];

	// note ith entry centered about i+1 in _wave space
	for (unsigned i = 0; i < this->_config.nx - 2; i++) {
		_wave_xx_current[i] = (_wave_x_current[i + 1] - _wave_x_current[i]) / this->_config.dx;
	}

	// first wave temporal derivative - just assign to provided velocity
	auto& _wave_t_current = this->_wave_t[current_idx];
	auto& _wave_previous = this->_wave[previous_idx];

	for (unsigned i = 0; i < this->_config.nx; i++) {
		_wave_t_current[i] = (_wave_current[i] - _wave_previous[i]) / dt;
	}
}

void SimWire::_computeHeatDerivatives(float dt) {

	// first work out the indices
	unsigned int current_idx = this->_currentTimestepIndex;

	auto& _heat_current = this->_heat[current_idx];
	
	// first heat spatial derivative
	auto& _heat_x_current = this->_heat_x[current_idx];

	for (unsigned i = 0; i < this->_config.nx - 1; i++) {
		_heat_x_current[i] = (_heat_current[i + 1] - _heat_current[i]) / this->_config.dx;
	}

	// second heat spatial derivative
	auto& _heat_xx_current = this->_heat_xx[current_idx];

	for (unsigned i = 0; i < this->_config.nx - 2; i++) {
		_heat_xx_current[i] = (_heat_x_current[i + 1] - _heat_x_current[i]) / this->_config.dx;
	}
}

void SimWire::_updateWaveBoundaries(std::vector<float>&wave_next, float dt) {

	wave_next[0] =
		this->edge->getStartNode().getSimNode()->waveBoundary(this, WireEnd::START, dt);

	wave_next[this->_config.nx - 1] =
		this->edge->getEndNode().getSimNode()->waveBoundary(this, WireEnd::END, dt);
}

void SimWire::_updateHeatBoundaries(std::vector<float>&heat_next, float dt) {

	heat_next[0] =
		this->edge->getStartNode().getSimNode()->heatBoundary(this, WireEnd::START, dt);

	heat_next[this->_config.nx - 1] =
		this->edge->getEndNode().getSimNode()->heatBoundary(this, WireEnd::END, dt);
}

void SimWire::_updateTemporalIndex() {

	this->_currentTimestepIndex += 1;

	if (this->_currentTimestepIndex >= this->_config.storeTimesteps) {
		this->_currentTimestepIndex = 0;
	}
}
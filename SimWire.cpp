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
	unsigned int next_idx = (current_idx + 1) % this->config.storeTimesteps;
	unsigned int previous_idx = (this->config.storeTimesteps + current_idx - 1) %
		this->config.storeTimesteps;

	// compute derivatives
	this->computeWaveDerivatives(dt);
	this->computeHeatDerivatives(dt);

	// nice reference aliases for the current derivative vectors
	auto& wave =	this->wave[current_idx];
	auto& wave_x =	this->wave_x[current_idx];
	auto& wave_xx = this->wave_xx[current_idx];
	auto& wave_t =	this->wave_t[current_idx];
	auto& heat =	this->heat[current_idx];
	auto& heat_x =	this->heat_x[current_idx];
	auto& heat_xx = this->heat_xx[current_idx];

	auto& wave_previous = this->wave[previous_idx];

	// what we need to change
	auto& wave_next = this->wave[next_idx];
	auto& heat_next = this->heat[next_idx];

	// update the non-boundary wave bits
	float wave_tt;
	for (unsigned i = 1; i < this->config.nx - 1; i++) {

		wave_tt = std::pow(this->waveSpeed[i], 2) * wave_xx[i - 1] - 
			this->damping[i] * wave_t[i];

		wave_next[i] = std::pow(dt, 2) * wave_tt + 2 * wave[i] - wave_previous[i];
	}

	// we should store the 'energy lost' differential due to damping
	// so we can turn it into heat -> conserve energy

	// update the non-boundary heat bits
	for (unsigned int i = 1; i < this->config.nx - 1; i++) {

		heat_next[i] = dt * this->diffusivity[i] * heat_xx[i - 1] + heat[i];
	}

	// update the wave boundaries - trusting that our node pointers aren't null!
	updateWaveBoundaries(wave_next, dt);

	// update the heat boundaries
	updateHeatBoundaries(heat_next, dt);

	// update temporal index for the next cycle
	this->updateTemporalIndex();
}

bool SimWire::initialize(const Config& config, const InitState& initState, float dt) {

	// config set + validate
	if (!this->setConfig(config))
		return false;

	// reset circular buffer position
	this->_currentTimestepIndex = 0;

	// allocate the state vectors
	this->allocateState();

	// initialize the state vectors using the provided initializers
	this->initializeState(initState, dt);

	// might as well compute some derivatives while we're here
	this->computeWaveDerivatives(dt);
	this->computeHeatDerivatives(dt);

	unsigned int next_idx = this->getNextTemporalIndex();

	// update the wave boundaries - trusting that our node pointers aren't null!
	updateWaveBoundaries(this->wave[next_idx], dt);

	// update the heat boundaries
	updateHeatBoundaries(this->heat[next_idx], dt);

	// update indices
	this->updateTemporalIndex();

	// we're done!
	this->_isInitialized = true;

	return true;
}

// legacy interfaces
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
	assert(this->config.nx == initWave.size());
	assert(this->config.nx == initWaveVelocity.size());
	assert(this->config.nx == initHeat.size());

	// check dimensions of wire properties
	assert(this->config.nx == waveSpeed.size());
	assert(this->config.nx == damping.size());
	assert(this->config.nx == diffusivity.size());

	// values look okay, start storing stuff
	this->config.nx = config.nx;
	this->config.storeTimesteps = config.storeTimesteps;
	this->config.dx = config.dx;

	// resize wire property storage and store the new stuff
	this->waveSpeed.resize(this->config.nx);
	this->damping.resize(this->config.nx);
	this->diffusivity.resize(this->config.nx);

	for (unsigned i = 0; i < this->config.nx; i++) {

		this->waveSpeed[i] = waveSpeed[i];
		this->damping[i] = damping[i];
		this->diffusivity[i] = diffusivity[i];
	}

	// resize internal storage

	// wave magnitude
	this->wave.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave.size(); i++) {
		this->wave[i].resize(this->config.nx);
	}

	// heat magnitude
	this->heat.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat.size(); i++) {
		this->heat[i].resize(this->config.nx);
	}

	// wave magnitude time derivative
	this->wave_t.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_t.size(); i++) {
		this->wave_t[i].resize(this->config.nx);
	}

	// wave magnitude space derivative
	this->wave_x.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_x.size(); i++) {
		this->wave_x[i].resize(this->config.nx - 1);
	}

	// second wave magnitude space derivative
	this->wave_xx.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_xx.size(); i++) {
		this->wave_xx[i].resize(this->config.nx - 2);
	}

	// heat magnitude space derivative
	this->heat_x.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat_x.size(); i++) {
		this->heat_x[i].resize(this->config.nx - 1);
	}

	// second heat magnitude space derivative
	this->heat_xx.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat_xx.size(); i++) {
		this->heat_xx[i].resize(this->config.nx - 2);
	}

	// reset circular buffer position
	this->_currentTimestepIndex = 0;

	// set the given initial state
	auto& _wave_current = this->wave[this->_currentTimestepIndex];
	auto& _heat_current = this->heat[this->_currentTimestepIndex];
	auto& _wave_next = this->wave[(this->_currentTimestepIndex + 1) % this->config.storeTimesteps];
	auto& _heat_next = this->heat[(this->_currentTimestepIndex + 1) % this->config.storeTimesteps];

	for (unsigned i = 0; i < this->config.nx; i++) {

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
	this->computeWaveDerivatives(dt);
	this->computeHeatDerivatives(dt);

	// update the wave boundaries - trusting that our node pointers aren't null!
	updateWaveBoundaries(_wave_next, dt);

	// update the heat boundaries
	updateHeatBoundaries(_heat_next, dt);

	// update indices
	this->updateTemporalIndex();

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
	assert(this->config.nx == initWave.size());
	assert(this->config.nx == initWaveVelocity.size());
	assert(this->config.nx == initHeat.size());

	// check dimensions of wire properties
	assert(this->config.nx == waveSpeed.size());
	assert(this->config.nx == damping.size());
	assert(this->config.nx == diffusivity.size());

	// resize wire property storage and store the new stuff
	this->waveSpeed.resize(this->config.nx);
	this->damping.resize(this->config.nx);
	this->diffusivity.resize(this->config.nx);

	for (unsigned i = 0; i < this->config.nx; i++) {

		this->waveSpeed[i] = waveSpeed[i];
		this->damping[i] = damping[i];
		this->diffusivity[i] = diffusivity[i];
	}

	// resize internal storage

	// wave magnitude
	this->wave.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave.size(); i++) {
		this->wave[i].resize(this->config.nx);
	}

	// heat magnitude
	this->heat.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat.size(); i++) {
		this->heat[i].resize(this->config.nx);
	}

	// wave magnitude time derivative
	this->wave_t.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_t.size(); i++) {
		this->wave_t[i].resize(this->config.nx);
	}

	// wave magnitude space derivative
	this->wave_x.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_x.size(); i++) {
		this->wave_x[i].resize(this->config.nx - 1);
	}

	// second wave magnitude space derivative
	this->wave_xx.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_xx.size(); i++) {
		this->wave_xx[i].resize(this->config.nx - 2);
	}

	// heat magnitude space derivative
	this->heat_x.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat_x.size(); i++) {
		this->heat_x[i].resize(this->config.nx - 1);
	}

	// second heat magnitude space derivative
	this->heat_xx.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat_xx.size(); i++) {
		this->heat_xx[i].resize(this->config.nx - 2);
	}

	// reset circular buffer position
	this->_currentTimestepIndex = 0;

	// set the given initial state
	auto& _wave_current = this->wave[this->_currentTimestepIndex];
	auto& _heat_current = this->heat[this->_currentTimestepIndex];
	auto& _wave_next = this->wave[(this->_currentTimestepIndex + 1) % this->config.storeTimesteps];
	auto& _heat_next = this->heat[(this->_currentTimestepIndex + 1) % this->config.storeTimesteps];

	for (unsigned i = 0; i < this->config.nx; i++) {

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
	this->computeWaveDerivatives(dt);
	this->computeHeatDerivatives(dt);

	// update the wave boundaries - trusting that our node pointers aren't null!
	updateWaveBoundaries(_wave_next, dt);

	// update the heat boundaries
	updateHeatBoundaries(_heat_next, dt);

	// update indices
	this->updateTemporalIndex();

	// we're done!
	this->_isInitialized = true;

	return true;
}

const std::vector<float>& SimWire::getWave() const {

	return this->wave[this->_currentTimestepIndex];
}

const std::vector<float>& SimWire::getHeat() const {
	
	return this->heat[this->_currentTimestepIndex];
}

const std::vector<float>& SimWire::getWavePast(unsigned int n) const {

	assert(n < this->config.storeTimesteps);

	return this->wave[(this->_currentTimestepIndex + n) % this->config.storeTimesteps];
}

const std::vector<float>& SimWire::getHeatPast(unsigned int n) const {

	assert(n < this->config.storeTimesteps);

	return this->heat[(this->_currentTimestepIndex + n) % this->config.storeTimesteps];
}

const std::vector<float>& SimWire::getWaveFuture() const {

	unsigned int next_idx = (this->_currentTimestepIndex + 1) % this->config.storeTimesteps;

	return this->wave[next_idx];
}

const std::vector<float>& SimWire::getHeatFuture() const {

	unsigned int next_idx = (this->_currentTimestepIndex + 1) % this->config.storeTimesteps;

	return this->heat[next_idx];
}

void SimWire::setStoreTimesteps(unsigned int storeTimesteps) {

	if (storeTimesteps < 3) {
		this->config.storeTimesteps = 3;
	} else {
		this->config.storeTimesteps = storeTimesteps;
	}
}

unsigned int SimWire::getStoreTimesteps() const {
	
	return this->config.storeTimesteps;
}

bool SimWire::setConfig(const Config& config) {

	// validation checks first
	if (config.dx > 0.f &&
		config.nx >= 4 &&
		config.storeTimesteps >= 3) {

		// valid -> store data
		this->config = config;
		this->_isConfigValid = true;

		return true;
	} else {

		return false;
	}
}

const SimWire::Config& SimWire::getConfig() const {

	return this->config;
}

bool SimWire::isConfigValid() const {

	return this->_isConfigValid;
}

bool SimWire::isInitialized() const {

	// TODO: do initialization checks here
	// don't just return _isInitialized!

	return this->_isInitialized;
}

void SimWire::computeWaveDerivatives(float dt) {

	// first work out the indices
	unsigned int current_idx = this->_currentTimestepIndex;
	unsigned int previous_idx = (this->config.storeTimesteps + current_idx - 1) %
		this->config.storeTimesteps;

	auto& _wave_current = this->wave[current_idx];

	// first wave spatial derivative
	auto& _wave_x_current = this->wave_x[current_idx];

	for (unsigned i = 0; i < this->config.nx - 1; i++) {
		_wave_x_current[i] = (_wave_current[i + 1] - _wave_current[i]) / this->config.dx;
	}

	// second wave spatial derivative
	auto& _wave_xx_current = this->wave_xx[current_idx];

	// note ith entry centered about i+1 in _wave space
	for (unsigned i = 0; i < this->config.nx - 2; i++) {
		_wave_xx_current[i] = (_wave_x_current[i + 1] - _wave_x_current[i]) / this->config.dx;
	}

	// first wave temporal derivative - just assign to provided velocity
	auto& _wave_t_current = this->wave_t[current_idx];
	auto& _wave_previous = this->wave[previous_idx];

	for (unsigned i = 0; i < this->config.nx; i++) {
		_wave_t_current[i] = (_wave_current[i] - _wave_previous[i]) / dt;
	}
}

void SimWire::computeHeatDerivatives(float dt) {

	// first work out the indices
	unsigned int current_idx = this->_currentTimestepIndex;

	auto& _heat_current = this->heat[current_idx];
	
	// first heat spatial derivative
	auto& _heat_x_current = this->heat_x[current_idx];

	for (unsigned i = 0; i < this->config.nx - 1; i++) {
		_heat_x_current[i] = (_heat_current[i + 1] - _heat_current[i]) / this->config.dx;
	}

	// second heat spatial derivative
	auto& _heat_xx_current = this->heat_xx[current_idx];

	for (unsigned i = 0; i < this->config.nx - 2; i++) {
		_heat_xx_current[i] = (_heat_x_current[i + 1] - _heat_x_current[i]) / this->config.dx;
	}
}

void SimWire::updateWaveBoundaries(std::vector<float>&wave_next, float dt) {

	wave_next[0] =
		this->edge->getStartNode().getSimNode()->waveBoundary(this, WireEnd::START, dt);

	wave_next[this->config.nx - 1] =
		this->edge->getEndNode().getSimNode()->waveBoundary(this, WireEnd::END, dt);
}

void SimWire::updateHeatBoundaries(std::vector<float>&heat_next, float dt) {

	heat_next[0] =
		this->edge->getStartNode().getSimNode()->heatBoundary(this, WireEnd::START, dt);

	heat_next[this->config.nx - 1] =
		this->edge->getEndNode().getSimNode()->heatBoundary(this, WireEnd::END, dt);
}

void SimWire::updateTemporalIndex() {

	this->_currentTimestepIndex += 1;

	if (this->_currentTimestepIndex >= this->config.storeTimesteps) {
		this->_currentTimestepIndex = 0;
	}
}

unsigned int SimWire::getNextTemporalIndex() {

	return (this->_currentTimestepIndex + 1) % this->config.storeTimesteps;
}

// allocate using the stored config
void SimWire::allocateState() {

	if (!isConfigValid())
		return;

	// wave magnitude
	this->wave.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave.size(); i++) {
		this->wave[i].resize(this->config.nx);
	}

	// heat magnitude
	this->heat.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat.size(); i++) {
		this->heat[i].resize(this->config.nx);
	}

	// wave magnitude time derivative
	this->wave_t.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_t.size(); i++) {
		this->wave_t[i].resize(this->config.nx);
	}

	// wave magnitude space derivative
	this->wave_x.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_x.size(); i++) {
		this->wave_x[i].resize(this->config.nx - 1);
	}

	// second wave magnitude space derivative
	this->wave_xx.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->wave_xx.size(); i++) {
		this->wave_xx[i].resize(this->config.nx - 2);
	}

	// heat magnitude space derivative
	this->heat_x.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat_x.size(); i++) {
		this->heat_x[i].resize(this->config.nx - 1);
	}

	// second heat magnitude space derivative
	this->heat_xx.resize(this->config.storeTimesteps);
	for (unsigned i = 0; i < this->heat_xx.size(); i++) {
		this->heat_xx[i].resize(this->config.nx - 2);
	}
}

void SimWire::initializeState(const InitState& initState, float dt) {

	// use the state builders to fill the vectors
	// references to state builders
	auto& initWaveBuilder = *initState.initWave.get();
	auto& initWaveVelocityBuilder = *initState.initWaveVelocity.get();
	auto& initHeatBuilder = *initState.initHeat.get();
	auto& waveSpeedBuilder = *initState.waveSpeed.get();
	auto& dampingBuilder = *initState.damping.get();
	auto& diffusivityBuilder = *initState.diffusivity.get();

	// indices - we only initialize the timesteps we need to
	unsigned int current_idx = this->_currentTimestepIndex;
	unsigned int next_idx = (current_idx + 1) % this->config.storeTimesteps;

	initWaveBuilder(this->wave[current_idx]);
	initHeatBuilder(this->heat[current_idx]);

	// for good measure
	initHeatBuilder(this->heat[next_idx]);
	
	waveSpeedBuilder(this->waveSpeed);
	dampingBuilder(this->damping);
	diffusivityBuilder(this->diffusivity);

	// temp buffer for the velocity
	std::vector<float> waveVelocity;
	waveVelocity.resize(this->config.nx);
	initWaveVelocityBuilder(waveVelocity);

	auto& wave_current = this->wave[current_idx];
	auto& wave_next = this->wave[next_idx];

	// calculate the next idx based on the velocity
	for (unsigned i = 0; i < this->config.nx; i++) 
		wave_next[i] = wave_current[i] + waveVelocity[i] * dt;
}
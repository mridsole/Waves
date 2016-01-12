#include "stdafx.h"
#include "SimulationWire.h"
#include "SimulationNode.h"

#include <algorithm>
#include <cmath>
#include <assert.h>

using namespace sim;

SimulationWire::SimulationWire() {

	
}

SimulationWire::~SimulationWire() {

	// remove the links to both our connected nodes, if nobody did already
	this->removeBoundaryNode(WireEnd::START);
	this->removeBoundaryNode(WireEnd::START);
}

void SimulationWire::update(float dt) {

	// assuming we updated temporal index last time
	// get the indices
	unsigned int current_idx = this->_currentTimestepIndex;
	unsigned int next_idx = (current_idx + 1) % this->_storeTimesteps;
	unsigned int previous_idx = (this->_storeTimesteps + current_idx - 1) % 
		this->_storeTimesteps;

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
	for (unsigned i = 1; i < this->_nx - 1; i++) {

		wave_tt = std::pow(this->_waveSpeed[i], 2) * wave_xx[i - 1] - 
			this->_damping[i] * wave_t[i];

		wave_next[i] = std::pow(dt, 2) * wave_tt + 2 * wave[i] - wave_previous[i];
	}

	// update the non-boundary heat bits
	for (unsigned int i = 1; i < this->_nx - 1; i++) {

		heat_next[i] = dt * std::pow(this->_diffusivity[i], 2) * heat_xx[i - 1] + heat[i];
	}

}

// hnnng
void SimulationWire::initialize(SimulationWireConfig config, 
	std::vector<float>& initWave,
	std::vector<float>& initWaveVelocity, 
	std::vector<float>& initHeat, 
	std::vector<float>& waveSpeed,
	std::vector<float>& damping, 
	std::vector<float>& diffusivity,
	float dt) {

	assert(config.nx > 2);
	assert(config.dx > 0.f);

	// check the dimensions of everything
	assert(config.nx == initWave.size());
	assert(config.nx == initWaveVelocity.size());
	assert(config.nx == initHeat.size());

	// check dimensions of wire properties
	assert(config.nx == waveSpeed.size());
	assert(config.nx == damping.size());
	assert(config.nx == diffusivity.size());

	// make sure the values make sense
	// three's the magic number
	assert(config.storeTimesteps > 3);

	// values look okay, start storing things
	this->_nx = config.nx;
	this->_storeTimesteps = config.storeTimesteps;
	this->_dx = config.dx;

	// resize wire property storage and store the new shit
	this->_waveSpeed.resize(this->_nx);
	this->_damping.resize(this->_nx);
	this->_diffusivity.resize(this->_nx);

	for (unsigned i = 0; i < this->_nx; i++) {

		this->_waveSpeed[i] = waveSpeed[i];
		this->_damping[i] = damping[i];
		this->_diffusivity[i] = diffusivity[i];
	}

	// resize internal storage

	// wave magnitude
	this->_wave.resize(this->_storeTimesteps);
	for (unsigned i = 0; i < this->_wave.size(); i++) {
		this->_wave[i].resize(this->_nx);
	}

	// heat magnitude
	this->_heat.resize(this->_storeTimesteps);
	for (unsigned i = 0; i < this->_heat.size(); i++) {
		this->_heat[i].resize(this->_nx);
	}

	// wave magnitude time derivative
	this->_wave_t.resize(this->_storeTimesteps);
	for (unsigned i = 0; i < this->_wave_t.size(); i++) {
		this->_wave_t[i].resize(this->_nx);
	}

	// wave magnitude space derivative
	this->_wave_x.resize(this->_storeTimesteps);
	for (unsigned i = 0; i < this->_wave_x.size(); i++) {
		this->_wave_x[i].resize(this->_nx - 1);
	}

	// second wave magnitude space derivative
	this->_wave_xx.resize(this->_storeTimesteps);
	for (unsigned i = 0; i < this->_wave_xx.size(); i++) {
		this->_wave_x[i].resize(this->_nx - 2);
	}

	// heat magnitude space derivative
	this->_heat_x.resize(this->_storeTimesteps);
	for (unsigned i = 0; i < this->_heat_x.size(); i++) {
		this->_heat_x[i].resize(this->_nx - 1);
	}

	// second heat magnitude space derivative
	this->_heat_xx.resize(this->_storeTimesteps);
	for (unsigned i = 0; i < this->_heat_xx.size(); i++) {
		this->_heat_xx[i].resize(this->_nx - 2);
	}

	// reset circular buffer position
	this->_currentTimestepIndex = 0;

	// set the given initial state
	auto& _wave_current = this->_wave[this->_currentTimestepIndex];
	auto& _heat_current = this->_heat[this->_currentTimestepIndex];
	auto& _wave_next = this->_wave[(this->_currentTimestepIndex + 1) % this->_storeTimesteps];
	auto& _heat_next = this->_heat[(this->_currentTimestepIndex + 1) % this->_storeTimesteps];

	for (unsigned i = 0; i < this->_nx; i++) {

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

	// update indices
	this->_updateTemporalIndex();

	// we're done!
	this->_isInitialized = true;
}

const std::vector<float>& SimulationWire::getWave() const {

	return this->_wave[this->_currentTimestepIndex];
}

const std::vector<float>& SimulationWire::getHeat() const {
	
	return this->_heat[this->_currentTimestepIndex];
}

const std::vector<float>& SimulationWire::getWavePast(unsigned int n) const {

	assert(n < this->_storeTimesteps);

	return this->_wave[(this->_currentTimestepIndex + n) % this->_storeTimesteps];
}

const std::vector<float>& SimulationWire::getHeatPast(unsigned int n) const {

	assert(n < this->_storeTimesteps);

	return this->_heat[(this->_currentTimestepIndex + n) % this->_storeTimesteps];
}

int SimulationWire::setBoundaryNode(SimulationNode* node, WireEnd wireEnd) {

	// don't make a boo boo
	assert(node != nullptr);

	// remove the old node
	this->removeBoundaryNode(wireEnd);

	// set the new node
	if (wireEnd == WireEnd::START) {
		this->_bcNodeStart = node;
	} else {
		this->_bcNodeEnd = node;
	}

	// check if there's already a connection to this wire end
	auto wireEndPairIt = std::find(node->wires.begin(), node->wires.end(),
		std::pair<SimulationWire*, WireEnd>(this, wireEnd));

	if (wireEndPairIt != node->wires.end()) {

		// if there is, don't do anything
		return 1;
	} else {

		// otherwise, add the connection
		node->wires.push_back(std::pair<SimulationWire*, WireEnd>(this, wireEnd));
		return 0;
	}
}

SimulationNode* SimulationWire::getBoundaryNode(WireEnd wireEnd) {

	// no guarentee the returned pointer won't be null!
	if (wireEnd == WireEnd::START) {
		return this->_bcNodeStart;
	} else {
		return this->_bcNodeEnd;
	}
}

int SimulationWire::removeBoundaryNode(WireEnd wireEnd) {

	SimulationNode* node = this->getBoundaryNode(wireEnd);

	if (node == nullptr)
		return -1;

	// remove the link in the SimulationNode
	// note we're not calling the public function but rather
	// using friend privileges to directly access the storage

	auto wireEndPairIt = std::find(node->wires.begin(), node->wires.end(),
		std::pair<SimulationWire*, WireEnd>(this, wireEnd));

	// for now

	if (wireEndPairIt != node->wires.end()) {
		node->wires.erase(wireEndPairIt);
	} else {
		// the node wasn't storing a reference to this wire anyway,
		// so we didn't really 'remove' anything
	}

	// finally, set the stored pointer to null
	if (wireEnd == WireEnd::START) {
		this->_bcNodeStart = nullptr;
	} else {
		this->_bcNodeEnd = nullptr;
	}

	return 0;
}

void SimulationWire::setStoreTimesteps(unsigned int storeTimesteps) {

	if (storeTimesteps < 3) {
		this->_storeTimesteps = 3;
	} else {
		this->_storeTimesteps = storeTimesteps;
	}
}

unsigned int SimulationWire::getStoreTimesteps() const {
	
	return this->_storeTimesteps;
}

bool SimulationWire::isInitialized() const {

	// TODO: do initialization checks here
	// don't just return _isInitialized!

	return this->_isInitialized;
}

void SimulationWire::_computeWaveDerivatives(float dt) {

	// first work out the indices
	unsigned int current_idx = this->_currentTimestepIndex;
	unsigned int previous_idx = (this->_currentTimestepIndex + current_idx - 1) %
		this->_currentTimestepIndex;

	auto& _wave_current = this->_wave[current_idx];

	// first wave spatial derivative
	auto& _wave_x_current = this->_wave_x[current_idx];

	for (unsigned i = 0; i < this->_nx - 1; i++) {
		_wave_x_current[i] = (_wave_current[i + 1] - _wave_current[i]) / this->_dx;
	}

	// second wave spatial derivative
	auto& _wave_xx_current = this->_wave_xx[current_idx];

	// note ith entry centered about i+1 in _wave space
	for (unsigned i = 0; i < this->_nx - 2; i++) {
		_wave_xx_current[i] = (_wave_x_current[i + 1] - _wave_x_current[i]) / this->_dx;
	}

	// first wave temporal derivative - just assign to provided velocity
	auto& _wave_t_current = this->_wave_t[current_idx];
	auto& _wave_previous = this->_wave_t[previous_idx];

	for (unsigned i = 0; i < this->_nx; i++) {
		_wave_t_current[i] = (_wave_current[i] - _wave_previous[i]) / dt;
	}
}

void SimulationWire::_computeHeatDerivatives(float dt) {

	// first work out the indices
	unsigned int current_idx = this->_currentTimestepIndex;

	auto& _heat_current = this->_heat[current_idx];
	
	// first heat spatial derivative
	auto& _heat_x_current = this->_heat_x[current_idx];

	for (unsigned i = 0; i < this->_nx - 1; i++) {
		_heat_x_current[i] = (_heat_current[i + 1] - _heat_current[i]) / this->_dx;
	}

	// second heat spatial derivative
	auto& _heat_xx_current = this->_heat_xx[current_idx];

	for (unsigned i = 0; i < this->_nx - 2; i++) {
		_heat_xx_current[i] = (_heat_x_current[i + 1] - _heat_x_current[i]) / this->_dx;
	}
}

void SimulationWire::_updateTemporalIndex() {

	this->_currentTimestepIndex += 1;

	if (this->_currentTimestepIndex >= this->_storeTimesteps) {
		this->_currentTimestepIndex = 0;
	}
}
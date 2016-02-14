#include "stdafx.h"
#include "SimController.h"

#include <assert.h>

#include <stdio.h>

using namespace hwsim;

SimController::SimController(SimConfig config)
{
	this->setConfig(config);
}


SimController::~SimController()
{
}

void SimController::update() {

	float dt = this->_config.dt;

	// update all wires
	for (unsigned i = 0; i < this->_wires.size(); i++) {

		// this updates both wave and heat
		this->_wires[i]->update(dt);
	}

	// update devices here?
}

//SimWire* SimController::createWire() {
//
//	SimWire* newWire = new SimWire();
//	this->_wires.push_back(newWire);
//
//	return newWire;
//}
//
//SimWire* SimController::createConfigWire() {
//
//	SimWire* newWire = new SimWire(this->_config.defaultWireConfig);
//	this->_wires.push_back(newWire);
//
//	return newWire;
//}
//
//SimWire* SimController::createConfigWire(const SimWire::Config& config) {
//
//	SimWire* newWire = new SimWire(config);
//	this->_wires.push_back(newWire);
//
//	return newWire;
//}

bool SimController::initToDefaultConstants(SimWire* wire) {

	// creating copies of the default values for every wire initialization
	// is pretty inefficient - but this isn't a performance critical path
	// (and the wire is going to copy the copy anyway)

	// BIG boo boo
	assert(wire != nullptr);

	// if the wire isn't configured abort mission
	if (!wire->isConfigValid()) {
		return false;
	}

	// length of the wire in spacesteps
	unsigned int nx = wire->getConfig().nx;

	// make the default constant value vectors
	auto wave = std::vector<float>(nx, this->_config.defaultConstInit.wave);
	auto heat = std::vector<float>(nx, this->_config.defaultConstInit.heat);
	auto waveSpeed = std::vector<float>(nx, this->_config.defaultConstInit.waveSpeed);
	auto damping = std::vector<float>(nx, this->_config.defaultConstInit.damping);
	auto diffusivity = std::vector<float>(nx, this->_config.defaultConstInit.diffusivity);

	// we also need an initial velocity - just make it zero
	auto initVelocity = std::vector<float>(nx, 0.f);

	// initialize
	return wire->initialize(wave, initVelocity, heat, waveSpeed, damping, 
		diffusivity, this->_config.dt);
}

int SimController::deleteWire(SimWire& wire) {

	// see if we're currently storing it
	auto wireIt = std::find(this->_wires.begin(), this->_wires.end(), &wire);

	if (wireIt == this->_wires.end()) {

		// we're not keeping track of it -> not our responsibility!
		return -1;
	} else {

		// otherwise, remove it from the list
		this->_wires.erase(wireIt);

		// delete it (this will also remove the references in the bc nodes)
		delete &wire;

		return 0;
	}
}

//SimNode* SimController::createNode() {
//
//	SimNode* newNode = new SimNode();
//	this->_nodes.push_back(newNode);
//
//	return newNode;
//}

int SimController::deleteNode(SimNode& node) {

	// see if we're currently storing it
	auto nodeIt = std::find(this->_nodes.begin(), this->_nodes.end(), &node);

	if (nodeIt == this->_nodes.end()) {

		// not keeping track of it -> not our problem
		return -1;
	} else {

		// remove the node from the list
		this->_nodes.erase(nodeIt);

		// this will also remove the references from the wires
		delete &node;

		return 0;
	}
}

bool SimController::setConfig(const SimConfig& config) {
	
	this->_config = config;

	// TODO: DO VALIDATION HERE
	return true;
}

const SimConfig& SimController::getConfig() const {
	
	return this->_config;
}

bool SimController::isConfigValid() const {
	
	return this->_isConfigValid;
}
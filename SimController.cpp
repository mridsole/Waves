#include "stdafx.h"
#include "SimController.h"

#include <assert.h>

#include <stdio.h>

using namespace hwsim;
using Config = SimController::Config;

SimController::SimController(Config config) :
	timeElapsed(0.f),
	wires()
{
	this->setConfig(config);
}


SimController::~SimController()
{
}

void SimController::update() {

	// update all wires
	for (auto wire : wires) {
		wire->update(config.dt);	
	}
}

void SimController::reset() {

	timeElapsed = 0.f;

	// reset each wire
	for (auto wire : wires) {
		wire->reset(config.dt);
	}
}

// note these only add/remove the wire from the list
void SimController::addWire(SimWire* edge) {

	wires.push_back(edge);
}

void SimController::removeWire(SimWire* edge) {

	for (auto it = wires.begin(); it < wires.end(); it++) {
		if (*it == edge) {
			wires.erase(it);
			break;
		}
	}
}

bool SimController::setConfig(const Config& config) {
	
	this->config = config;

	// TODO: DO VALIDATION HERE
	return true;
}

const Config& SimController::getConfig() const {
	
	return this->config;
}

bool SimController::isConfigValid() const {
	
	return this->isConfigValid_;
}

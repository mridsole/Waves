#pragma once

#include "SimWire.h"
#include "SimNode.h"

namespace sim {

// stores various simulation parameters - dt, etc
struct SimConfig {

	// the differential time to more forward each step
	float dt;

	// the default configuration for a wire
	WireConfig defaultWireConfig;

	// the default constant initialization parameters for wires
	struct {
		float wave;
		float heat;
		float waveSpeed;
		float damping;
		float diffusivity;
	} defaultConstInit;
};

// responsible for keeping track of all wires and nodes
// managing memory, calling update functions, etc
class SimController
{

public:
	
	SimController(SimConfig config);
	~SimController();

	// update the simulation one timestep - calls step
	// on all tracked wires, nodes and devices
	void update();

	// create a new wire (config optional) and return pointer to it
	// configuration and initialization is up to the user!
	SimWire* createWire();

	// create and configure a wire
	SimWire* createConfigWire();
	SimWire* createConfigWire(const WireConfig& config);
	
	// initialize a wire to the defaults
	bool initToDefaultConstants(SimWire* wire);

	// delete a wire permanently, performing the necessary cleanup etc
	int deleteWire(SimWire& wire);

	// create a new node
	SimNode* createNode();

	// delete a node permanently, performing cleanup and all that
	int deleteNode(SimNode& node);

	// set/get sim config (true = passed validation)
	bool setConfig(const SimConfig& config);
	const SimConfig& getConfig() const;

	bool isConfigValid() const;

private:

	// the current simulation configuration
	SimConfig _config;

	// is the current sim configuration valid?
	bool _isConfigValid;

	// store all the wires
	std::vector<SimWire*> _wires;

	// store all the nodes
	std::vector<SimNode*> _nodes;
};

}
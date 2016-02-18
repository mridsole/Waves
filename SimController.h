#pragma once

#include "SimWire.h"
#include "SimNode.h"
#include "SimGraphInterface.h"

namespace hwsim {

// responsible for keeping track of all wires and nodes
// managing memory, calling update functions, etc
class SimController
{
	public:
	
	// add more here as required
	struct Config
	{
		float dt;
		
		// default constructor
		Config() :
			dt(0.0f)
		{};

		Config(float dt_) :
			dt(dt_)
		{};
	};	

	SimController(Config config);
	~SimController();

	// update the simulation one timestep - calls step
	// on all tracked wires, nodes and devices
	void update();
	
	// reset the simulation
	void reset();
	
	// set/get sim config (true = passed validation)
	bool setConfig(const Config& config);
	const Config& getConfig() const;

	bool isConfigValid() const;
	
	// just no reason to encapsulate things like this
	float timeElapsed;

private:
	
	friend class SimWire;
	friend class SimNode;
	friend class SimInitializer;

	// add a wire to the list
	void addWire(SimWire* wire);
	
	// the wire will remove itself when destroyed
	void removeWire(SimWire* wire);

	// the current simulation configuration
	Config config;

	// is the current sim configuration valid?
	bool isConfigValid_;

	// store all the wires
	std::vector<SimWire*> wires;
};

}

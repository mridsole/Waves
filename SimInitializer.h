#pragma once

#include "SimWire.h"
#include "SimNode.h"
#include "SimController.h"
#include "SimGraphInterface.h"

namespace hwsim {

// utility class for constructing and initializing SimWire objects
// based on provided default configurations and states
class SimInitializer
{

public:

	SimInitializer(SimController& simCtrl);
	~SimInitializer();

	void constructInitializeWire(SimWireEdge* edge);
	void constructWire(SimWireEdge* edge);
	void initializeWire(SimWireEdge* edge);

	void constructInitializeNode(SimNodeVertex* vertex);
	void constructNode(SimNodeVertex* vertex);
	void initializeNode(SimNodeVertex* vertex);

	SimWire::Config defaultWireConfig;
	SimWire::InitState defaultWireInitState;
	
	SimController& simCtrl;
};

// make a constant initializer real quick
class UniformWireStateInitializer : public hwsim::SimWire::StateInitializer
{

public:

	// utility - construct and wrap in a shared_ptr
	static std::shared_ptr<hwsim::SimWire::StateInitializer> Create(float _value)
	{
		return std::shared_ptr<hwsim::SimWire::StateInitializer>(
			new UniformWireStateInitializer(_value));
	}

	UniformWireStateInitializer(float _value) :
		value(_value)
	{};

	UniformWireStateInitializer() :
		value(0.f)
	{};

	void operator()(std::vector<float>& vec) const {

		// fill the vector with the default value
		for (unsigned i = 0; i < vec.size(); i++) {
			vec[i] = value;
		}
	}

	float value;
};

};

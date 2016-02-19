#include "stdafx.h"
#include "stdio.h"
#include <memory>

#include "UnitTest++/UnitTest++.h"

#include "CircuitGraph.h"

#include "SimGraphInterface.h"
#include "SimNode.h"
#include "SimWire.h"
#include "SimInitializer.h"

using namespace hwgame;
using UniformWireStateInitializer = hwsim::UniformWireStateInitializer;
using SimCtrlConfig = hwsim::SimController::Config;

float dt = 0.001f;

// an initializer for zeros
auto zeros = std::shared_ptr<hwsim::SimWire::StateInitializer>(new UniformWireStateInitializer(0.0f));

struct SimInitializerTestFixture {

	CircuitVertex* node1;
	CircuitVertex* node2;
	CircuitVertex* node3;
	CircuitEdge* edge1;
	CircuitEdge* edge2;
	CircuitEdge* edge3;

	// our sim initializer to test
	hwsim::SimInitializer simInit;

	// our sim controller
	hwsim::SimController simCtrl;

	SimInitializerTestFixture() :
		simCtrl(SimCtrlConfig(dt)),
		simInit(simCtrl)
	{

		// note how the graph is defined before anything to do
		// with the sim module is mentioned
		// a very simple test graph
		node1 = new CircuitVertex();
		node2 = new CircuitVertex();
		node3 = new CircuitVertex();
		edge1 = new CircuitEdge(node1, node2);
		edge2 = new CircuitEdge(node2, node3);
		edge3 = new CircuitEdge(node1, node3);

		// set the default config and initState for the initializer
		simInit.defaultWireConfig = hwsim::SimWire::Config(3, 200, 0.01f);

		// set up the default init state
		simInit.defaultWireInitState.damping = UniformWireStateInitializer::Create(0.1f);
		simInit.defaultWireInitState.waveSpeed = UniformWireStateInitializer::Create(1.f);
		simInit.defaultWireInitState.diffusivity = UniformWireStateInitializer::Create(0.01f);

		simInit.defaultWireInitState.initWave = zeros;
		simInit.defaultWireInitState.initWaveVelocity = zeros;
		simInit.defaultWireInitState.initHeat = zeros;
	};

	~SimInitializerTestFixture() {

		// this will leak memory!
		// but it doesn't really matter for one-off testing
	};

};

SUITE(SimInitializer)
{
	TEST_FIXTURE(SimInitializerTestFixture, InitializeFromDefaults)
	{
		// make a bunch of wires from the defaults
		simInit.constructInitializeWire(&edge1->data);
		simInit.constructInitializeWire(&edge2->data);
		simInit.constructInitializeWire(&edge3->data);

		// now make some nodes
		simInit.constructInitializeNode(&node1->data);
		simInit.constructInitializeNode(&node2->data);
		simInit.constructInitializeNode(&node3->data);

		// update using the sim controller
		for (unsigned i = 0; i < 500000; i++) {

			simCtrl.update();
		}
	}
}

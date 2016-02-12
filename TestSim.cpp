#include "stdafx.h"
#include "stdio.h"

#include "UnitTest++/UnitTest++.h"

#include "CircuitGraph.h"
#include "SimGraphInterface.h"

#include "SimNode.h"
#include "SimWire.h"

using namespace hwgame;

struct SimTestFixture {

	CircuitVertex* node1;
	CircuitVertex* node2;
	CircuitVertex* node3;
	CircuitEdge* edge1;
	CircuitEdge* edge2;
	CircuitEdge* edge3;

	float dt = 0.01f;

	SimTestFixture() {

		node1 = new CircuitVertex();
		node2 = new CircuitVertex();
		node3 = new CircuitVertex();
		edge1 = new CircuitEdge(node1, node2);
		edge2 = new CircuitEdge(node2, node3);
		edge3 = new CircuitEdge(node1, node3);

		// we have constructed a graph - now assign each node and edge a SimNode
		// and a SimWire
		node1->data.simNode = new hwsim::SimNode();
		node2->data.simNode = new hwsim::SimNode();
		node3->data.simNode = new hwsim::SimNode();

		edge1->data.simWire = new hwsim::SimWire();
		edge2->data.simWire = new hwsim::SimWire();
		edge3->data.simWire = new hwsim::SimWire();

		// setup the two way graph relationships
		node1->data.simNode->vertex = &node1->data;
		node2->data.simNode->vertex = &node2->data;
		node3->data.simNode->vertex = &node3->data;

		edge1->data.simWire->edge = &edge1->data;
		edge2->data.simWire->edge = &edge2->data;
		edge3->data.simWire->edge = &edge3->data;

		// initialize the sim wires
		hwsim::WireConfig cfg = { 3, 200, 0.01f };

		// set a bunch of initial values
		std::vector<float> zeroes(cfg.nx, 0.f);
		
		// other x-dependent properties (that we'll set as constant for now)
		std::vector<float> waveSpeed(cfg.nx, 10.f);
		std::vector<float> damping(cfg.nx, 1.f);
		std::vector<float> diffusivity(cfg.nx, 1.f);

		// initialize
		edge1->data.simWire->initialize(cfg, zeroes, zeroes, zeroes, waveSpeed, damping, diffusivity, dt);
		edge2->data.simWire->initialize(cfg, zeroes, zeroes, zeroes, waveSpeed, damping, diffusivity, dt);
		edge3->data.simWire->initialize(cfg, zeroes, zeroes, zeroes, waveSpeed, damping, diffusivity, dt);
	};

	~SimTestFixture() {

		// this will leak memory!
		// but it doesn't really matter for one-off testing
	};

};


SUITE(Sim) {

	TEST_FIXTURE(SimTestFixture, SimInitialization) {

		printf("running SimInitialization test ...\n");

		CHECK(edge1->data.simWire->edge == &edge1->data);

		// update our wires
		edge1->data.simWire->update(dt);
		edge2->data.simWire->update(dt);
		edge3->data.simWire->update(dt);
	}
}
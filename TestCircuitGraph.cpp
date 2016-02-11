#include "stdafx.h"
#include "stdio.h"

#include "UnitTest++/UnitTest++.h"

#include "CircuitGraph.h"
#include "SimWire.h"

using namespace hwgame;

struct CircuitGraphTestFixture {
	
	CircuitVertex* node1;
	CircuitVertex* node2;
	CircuitVertex* node3;

	CircuitEdge* edge1;
	CircuitEdge* edge2;
	CircuitEdge* edge3;

	CircuitGraphTestFixture() {

		node1 = new CircuitVertex();
		node2 = new CircuitVertex();
		node3 = new CircuitVertex();
		edge1 = new CircuitEdge(*node1, *node2);
		edge2 = new CircuitEdge(*node2, *node3);
		edge3 = new CircuitEdge(*node1, *node3);
	};

	~CircuitGraphTestFixture() {

		delete node1;
		node1 = nullptr;
		//delete node2;
		//delete node3;
	};

};


SUITE(CircuitGraph) {

	TEST_FIXTURE(CircuitGraphTestFixture, GraphValidity) {

		// check some things that have to be true at this point
		CHECK(node1->edges.size() == 2);
		CHECK(node1->edges[0] == edge1);
		CHECK(node1->edges[1] == edge3);
		CHECK(&edge1->startVertex == node1);
		CHECK(&edge1->endVertex == node2);
	}

	TEST_FIXTURE(CircuitGraphTestFixture, SimWireInterface) {

		// cast to our SimWireEdge interface and see what we can get
		hwsim::SimWireEdge* wireEdge1 = &edge1->data;
		
		CHECK(&wireEdge1->getStartNode() == (hwsim::SimNodeVertex*)(&node1->data));
	}
}
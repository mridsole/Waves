#include "stdafx.h"
#include "stdio.h"

#include "UnitTest++/UnitTest++.h"

#include "CircuitGraph.h"
#include "SimGraphInterface.h"

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
		edge1 = new CircuitEdge(node1, node2);
		edge2 = new CircuitEdge(node2, node3);
		edge3 = new CircuitEdge(node1, node3);
	};

	~CircuitGraphTestFixture() {

		// this will leak memory!
		// but it doesn't really matter for one-off testing
	};

};

SUITE(CircuitGraph) {

	TEST_FIXTURE(CircuitGraphTestFixture, GraphValidity) {

		// check some things that have to be true at this point
		CHECK(node1->edges.size() == 2);
		CHECK(node1->edges[0] == edge1);
		CHECK(node1->edges[1] == edge3);
		CHECK(edge1->startVertex == node1);
		CHECK(edge1->endVertex == node2);
	}

	TEST_FIXTURE(CircuitGraphTestFixture, EdgeDeletion) {

		// try deleting an edge and see if things still line up
		delete edge1;

		CHECK(node1->edges.size() == 1);
		CHECK(node2->edges.size() == 1);
		CHECK(node3->edges.size() == 2);
	}

	TEST_FIXTURE(CircuitGraphTestFixture, MixedDeletion) {

		// try deleting an edge, then a node that the edge was connected to
		delete edge1;

		CHECK(node1->edges.size() == 1);
		CHECK(node2->edges.size() == 1);

		delete node1;

		CHECK(node2->edges.size() == 1);
		CHECK(node3->edges.size() == 1);
	}

	TEST_FIXTURE(CircuitGraphTestFixture, SimWireInterface) {

		// cast to our SimWireEdge interface and see what we can get
		hwsim::SimWireEdge* wireEdge1 = &edge1->data;
		
		CHECK(&wireEdge1->getStartNode() == (hwsim::SimNodeVertex*)(&node1->data));
		CHECK(&wireEdge1->getEndNode() == (hwsim::SimNodeVertex*)(&node2->data));
		CHECK(wireEdge1->getSimWire() == edge1->data.simWire);
	}

	TEST_FIXTURE(CircuitGraphTestFixture, SimNodeInterface) {

		// similar to above
		hwsim::SimNodeVertex* nodeVertex1 = &node1->data;

		CHECK(nodeVertex1->getEdges().size() == 2);
		CHECK(&nodeVertex1->getEdges()[0]->getStartNode() == &node1->data);
		CHECK(&nodeVertex1->getEdges()[0]->getEndNode() == &node2->data);
	}
}
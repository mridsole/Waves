#include "stdafx.h"

#include "CircuitGraph.h"

using namespace hwgame;

// definitions for CircuitEdgeData:

hwsim::SimNodeVertex& CircuitEdgeData::getStartNode() {
	return edge->startVertex->data; 
};

hwsim::SimNodeVertex& CircuitEdgeData::getEndNode() {
	return edge->endVertex->data;
};

hwsim::SimWire* CircuitEdgeData::getWire() {
	return simWire;
}

void CircuitEdgeData::setWire(hwsim::SimWire* _wire) {
	simWire = _wire;
}

hwsim::SimWire::Config* CircuitEdgeData::getWireConfig() {
	return simWireConfig;
}

hwsim::SimWire::InitState* CircuitEdgeData::getInitState() {
	return simWireInitState;
}


// definitions for CircuitVertexData:

hwsim::SimNodeVertex::Edges& CircuitVertexData::getEdges() {

	// we have an std::vector<Node*>

	edgesBuffer.resize(0);
	for (auto it = vertex->edges.begin(); it < vertex->edges.end(); it++) {
		edgesBuffer.push_back(&((*it)->data));
	}

	return edgesBuffer;
};

hwsim::SimNode* CircuitVertexData::getSimNode() {

	return simNode;
}
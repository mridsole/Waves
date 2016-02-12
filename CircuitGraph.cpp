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

hwsim::SimWire* CircuitEdgeData::getSimWire() {
	
	return simWire;
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
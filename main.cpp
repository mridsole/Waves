#include "stdafx.h"

#include "HeatWave.h"

#include "DirectedGraph.h"

#include <utility>
#include <vector>

using namespace hwgame;

#include "stdio.h"

using CircuitGraph = graph::DirectedGraph<float, int>;
using CircuitEdge = CircuitGraph::Edge;
using CircuitNode = CircuitGraph::Node;

// program entry
int main() {

	CircuitGraph* testGraph = new CircuitGraph();

	CircuitNode* node1 = testGraph->createNode(1);
	CircuitNode* node2 = testGraph->createNode(5);
	CircuitEdge* edge1 = testGraph->createEdge(node1, node2, 2.1f);

	for (unsigned i = 0; i < 10000; i++)
		testGraph->createNode(i);

}
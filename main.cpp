#include "stdafx.h"

#include "HeatWave.h"

#include "DirectedGraph.h"

#include <utility>
#include <vector>

using namespace hwgame;

#include "stdio.h"

using CircuitEdge = dirgraph::Edge<float, int>;
using CircuitNode = dirgraph::Vertex<float, int>;

struct CircuitEdgeData 
{
	
};

// program entry
int main() {

	CircuitNode* node1 = new CircuitNode(1);
	CircuitNode* node2 = new CircuitNode(5);

	CircuitEdge* edge1 = new CircuitEdge(*node1, *node2, 10.5f);
}
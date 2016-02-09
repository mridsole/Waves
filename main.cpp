// entry point!

#include "stdafx.h"

#include <vector>

#include "HeatWave.h"

#include "CircuitGraph.h"

using namespace hwgame;

// program entry
int main() {

	//HeatWave* game = new HeatWave();
	//game->start();

	// well actually let's test graphs

	CircuitGraph testGraph;
	auto testNode1 = testGraph.createNode();
	auto testNode2 = testGraph.createNode();
	auto testEdge1 = testGraph.createEdge(testNode1, testNode2);
}
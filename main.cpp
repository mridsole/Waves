#include "stdafx.h"

#include "HeatWave.h"

#include "DirectedGraph.h"

#include <utility>
#include <vector>

using namespace hwgame;

#include "stdio.h"

// funky forward decl stuff
struct CircuitEdgeData;
struct CircuitVertexData;

using CircuitEdge = dirgraph::Edge<CircuitEdgeData, CircuitVertexData>;
using CircuitVertex = dirgraph::Vertex<CircuitEdgeData, CircuitVertexData>;
using CircuitEdgeDataBase = dirgraph::EdgeData<CircuitEdgeData, CircuitVertexData>;
using CircuitVertexDataBase = dirgraph::VertexData<CircuitEdgeData, CircuitVertexData>;

struct CircuitEdgeData : public CircuitEdgeDataBase
{
	float x;
	float y;

	CircuitEdgeData(CircuitEdge* _thisEdge, float _x, float _y) :
		CircuitEdgeDataBase::EdgeData(_thisEdge),
		x(_x), y(_y)
	{};
};

struct CircuitVertexData : public CircuitVertexDataBase
{
	float z;

	CircuitVertexData(CircuitVertex* _thisVertex, float _z) :
		CircuitVertexDataBase::VertexData(_thisVertex),
		z(_z)
	{};
};

// program entry
int main() {

	// make some nodes!
	CircuitVertex* node1 = new CircuitVertex(10.f);
	CircuitVertex* node2 = new CircuitVertex(21.5f);

	// get the data of node 1
	auto& node1data = node1->data;

	// do some things ...

	// maybe we don't have node1 anymore - how to get it back?
	CircuitVertex* node1again = node1data.vertex;

	// this is why we did all that template mess above - to facilitate a two-way
	// relationship between the node and it's data type. 
}
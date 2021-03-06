#pragma once

#include "SimGraphInterface.h"
#include "SimWire.h"
#include "SimNode.h"
#include "DirectedGraph.h"

namespace hwgame {
	
// funky forward decl stuff
struct CircuitEdgeData;
struct CircuitVertexData;

using CircuitEdge = dirgraph::Edge<CircuitEdgeData, CircuitVertexData>;
using CircuitVertex = dirgraph::Vertex<CircuitEdgeData, CircuitVertexData>;

// CircuitEdgeData and CircuitVertexData inherit a type parameterised by themselves - nice
// actually this is just a case of the curiously recurring template pattern
using CircuitEdgeDataBase = dirgraph::EdgeData<CircuitEdgeData, CircuitVertexData>;
using CircuitVertexDataBase = dirgraph::VertexData<CircuitEdgeData, CircuitVertexData>;

struct CircuitEdgeData : public CircuitEdgeDataBase, public hwsim::SimWireEdge
{
	// the simulation data for this wire
	hwsim::SimWire* simWire;

	// the initialization configuration and state
	// used for customized initialization - set to nullptr to use defaults
	hwsim::SimWire::Config* simWireConfig;
	hwsim::SimWire::InitState* simWireInitState;

	CircuitEdgeData(CircuitEdge* _thisEdge) :
		CircuitEdgeDataBase::EdgeData(_thisEdge),
		simWire(nullptr),
		simWireConfig(nullptr),
		simWireInitState(nullptr)
	{};

	// satisfy SimWireEdge
	hwsim::SimNodeVertex& getStartNode();
	hwsim::SimNodeVertex& getEndNode();
	hwsim::SimWire* getWire();
	void setWire(hwsim::SimWire* _wire);
	hwsim::SimWire::Config* getWireConfig();
	hwsim::SimWire::InitState* getInitState();
};

struct CircuitVertexData : public CircuitVertexDataBase, public hwsim::SimNodeVertex
{
	hwsim::SimNode* simNode;

	CircuitVertexData(CircuitVertex* _thisVertex) :
		CircuitVertexDataBase::VertexData(_thisVertex)
	{};

	// satisfy SimNodeVertex
	virtual Edges& getEdges();
	hwsim::SimNode* getSimNode();
	void setSimNode(hwsim::SimNode* simNode);

private:

	// getEdges implementation
	Edges edgesBuffer;
};

};
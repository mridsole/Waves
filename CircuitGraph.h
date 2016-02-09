#pragma once

#include "DirectedGraph.h"

namespace hwgame {

using DirectedGraph = graph::DirectedGraph;

class CircuitGraph : public DirectedGraph 
{

public:

	struct Edge;
	struct Node;

	struct Edge : public DirectedGraph::Edge
	{
		float x;

		Edge(DirectedGraph::Node* _startNode, DirectedGraph::Node* _endNode) :
			DirectedGraph::Edge::Edge(_startNode, _endNode)
		{};
	};

	struct Node : public DirectedGraph::Node
	{
		float y;

		Node() :
			DirectedGraph::Node::Node()
		{};
	};

	// 

	CircuitGraph() {};
	~CircuitGraph() {};

	Node* createNode() {

		Node* node = DirectedGraph::createNode<Node>();
		return node;
	};

	Edge* createEdge(DirectedGraph::Node* startNode, DirectedGraph::Node* endNode) {

		Edge* edge = DirectedGraph::createEdge<Edge>(startNode, endNode);
		return edge;
	};
};

};
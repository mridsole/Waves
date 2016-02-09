#pragma once

#include <vector>
#include <stdexcept>

namespace graph {

class DirectedGraph {

public:
	
	// forward declarations
	struct Edge;
	struct Node;
	struct Connection;

	using Edges = std::vector<Edge*>;
	using Nodes = std::vector<Node*>;
	using Connections = std::vector<Connection>;

	struct Edge
	{
		friend class DirectedGraph;

		Node* startNode;
		Node* endNode;

		// can only be constructed by DirectedGraph::createEdge
	protected:
		Edge(Node* _startNode, Node* _endNode) :
			startNode(_startNode),
			endNode(_endNode)
		{};

		virtual ~Edge() {};
	};

	struct Node
	{
		friend class DirectedGraph;

		Connections connections;

	protected:
		Node() : connections() {};
		virtual ~Node() {};
	};

	struct Connection
	{
		friend class DirectedGraph;

		Edge* edge;
		Node* node;
		bool end;

		bool operator==(const Connection& rhs) {
			return edge == rhs.edge && node == rhs.node && end == rhs.end;
		}

	protected:
		Connection(Edge* _edge, Node* _node, bool _end) :
			edge(_edge),
			node(_node),
			end(_end)
		{};
	};
	
	// DirectedGraph stuff
	DirectedGraph() {};
	~DirectedGraph() {};

	template <typename NodeType>
	NodeType* createNode() {

		NodeType* node = new NodeType();
		nodes.push_back(node);
		return node;
	}

	template <typename EdgeType>
	EdgeType* createEdge(Node* startNode, Node* endNode) {

		if (startNode == nullptr && endNode == nullptr)
			throw std::invalid_argument("Error creating edge: both nodes can't be null.");

		EdgeType* edge = new EdgeType(startNode, endNode);

		if (startNode != nullptr)
			startNode->connections.push_back(Connection(edge, startNode, false));

		if (endNode != nullptr)
			endNode->connections.push_back(Connection(edge, endNode, true));

		edges.push_back(edge);
		return edge;
	}

	template <typename NodeType, typename... Ts>
	NodeType* emplaceNode(Ts&&... args) {

		NodeType* node = new NodeType(args...);
		nodes.push_back(node);
		return node;
	}

	template <typename EdgeType, typename... Ts>
	EdgeType* emplaceEdge(Node* startNode, Node* endNode, Ts&&... args) {

		if (startNode == nullptr && endNode == nullptr)
			throw std::invalid_argument("Error creating edge: both nodes can't be null.");

		EdgeType* edge = new EdgeType(startNode, endNode, args...);

		if (startNode != nullptr)
			startNode->connections.push_back(Connection(edge, startNode, false));

		if (endNode != nullptr)
			endNode->connections.push_back(Connection(edge, endNode, true));
		
		edges.push_back(edge);
		return edge;
	}

	Connection* findConnection(Edge* edge, Node* node) {

		for (auto it = node->connections.end() - 1; it >= node->connections.begin(); it--) {
			if (it->edge == edge)
				return &(*it);
		}

		return nullptr;
	}

	// remove an edge from the graph and delete it
	void deleteEdge(Edge* edge) {

		if (edge == nullptr)
			return;

		// remove connections from the connected nodes
		Connection* connectionStart = findConnection(edge, edge->startNode);
		Connection* connectionEnd = findConnection(edge, edge->endNode);

		if (connectionStart != nullptr)
			removeConnection(*connectionStart);

		if (connectionEnd != nullptr)
			removeConnection(*connectionEnd);

		delete edge;
	}

	// remove a node from the graph and delete it
	void deleteNode(Node* node) {

		if (node == nullptr)
			return;

		// remove all the node's connections to edges
		for (auto it = node->connections.end() - 1; it >= node->connections.begin(); it--) {
			
			if (it->end)
				it->edge->endNode = nullptr;
			else
				it->edge->startNode = nullptr;
		}

		// delete the node
		delete node;
	}

	// remove a connection from the graph
	void removeConnection(Connection& connection) {

		if (connection.node == nullptr || connection.edge == nullptr)
			return;

		if (connection.end)
			connection.edge->endNode = nullptr;
		else
			connection.edge->startNode = nullptr;

		Node* node = connection.node;
		for (auto it = node->connections.end() - 1; it >= node->connections.begin(); it--) {
			if (*it == connection) {
				node->connections.erase(it);
			}
		}
	}

	// does every edge have two nodes on it?
	bool isGraphClosed() {

		for (auto it = edges.begin(); it < edges.end(); it++) {
			if ((*it)->startNode == nullptr || (*it)->endNode == nullptr)
				return false;
		}

		return true;
	}



protected:

	Edges edges;
	Nodes nodes;
};

};
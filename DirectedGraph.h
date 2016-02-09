#include <vector>
#include <stdexcept>

// debugging
#include "stdio.h"

// directed graph
namespace graph {

template <typename EdgeT, typename NodeT>
class DirectedGraph
{

public:

	// forward declarations
	struct Edge;
	struct Node;

	struct Connection
	{
		Edge* edge;
		Node* node;
		bool end;

		Connection(Edge* _edge, Node* _node, bool _end) :
			edge(_edge),
			node(_node),
			end(_end)
		{};
	};

	using Connections = std::vector<Connection>;
	using Edges = std::vector<Edge>;
	using Nodes = std::vector<Node>;

	// actual implementations
	struct Edge
	{
		friend class DirectedGraph;

		Node* startNode;
		Node* endNode;
		EdgeT data;

		// can only be constructed by DirectedGraph::createEdge
		//private:

		template <typename... Ts>
		Edge(Node* _startNode, Node* _endNode, Ts&&... args) :
			startNode(_startNode),
			endNode(_endNode),
			data(args...)
		{};

		// copy constructors
		Edge(Edge&& rhs) :
			startNode(rhs.startNode),
			endNode(rhs.endNode),
			data(rhs.data)
		{};

		Edge(Edge& rhs) :
			startNode(rhs.startNode),
			endNode(rhs.endNode),
			data(rhs.data)
		{};

		~Edge() {};
	};

	struct Node
	{
		friend class DirectedGraph;

		Connections connections;
		NodeT data;

		template <typename... Ts>
		Node(Ts&&... args) :
			data(args...)
		{};

		// copy constructors - need these to avoid obscure errors!
		Node(Node&& rhs) :
			connections(rhs.connections),
			data(rhs.data)
		{};

		Node(Node& rhs) :
			connections(rhs.connections),
			data(rhs.data)
		{};

		~Node() {};
	};

	// DirectedGraph stuff
	DirectedGraph() {};
	~DirectedGraph() {};

	template <typename... Ts>
	Edge& createEdge(Node* _startNode, Node* _endNode, Ts&&... args) {

		if (_startNode == nullptr && _endNode == nullptr)
			throw std::invalid_argument("Error creating edge: both node pointers cannot be null.");

		// create the edge in place in our edges vector, then get a pointer to it
		this->edges.emplace_back(_startNode, _endNode, args...);
		Edge* edge = &(*(this->edges.end() - 1));

		// give the pointer to our nodes
		if (_startNode != nullptr)
			_startNode->connections.emplace_back(edge, _startNode, false);

		if (_endNode != nullptr)
			_endNode->connections.emplace_back(edge, _endNode, false);

		return *edge;
	}

	Node& createNode(NodeT args) {

		this->nodes.emplace_back(args);
		DirectedGraph<EdgeT, NodeT>::Node* node = &(*(this->nodes.end() - 1));

		return *node;
	}


	// node centric - store a list of all the nodes
	Nodes nodes;

	// might as well store some edges too
	Edges edges;
};

};
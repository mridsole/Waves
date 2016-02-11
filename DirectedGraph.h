#include <vector>
#include <array>
#include <stdexcept>
#include "assert.h"

// debugging
#include "stdio.h"

// directed graph
namespace dirgraph {

template <typename EdgeT, typename VertexT>
struct Edge;

template <typename EdgeT, typename VertexT>
struct Vertex;

// EdgeT and VertexT must inherit from these! this is so that
// the data has access to the graph itself
template <typename EdgeT, typename VertexT>
struct EdgeData
{
	Edge<EdgeT, VertexT>* edge;

	EdgeData(Edge<EdgeT, VertexT>* _edge) :
		edge(_edge)
	{};
};

template <typename EdgeT, typename VertexT>
struct VertexData
{
	Vertex<EdgeT, VertexT>* vertex;

	VertexData(Vertex<EdgeT, VertexT>* _vertex) :
		vertex(_vertex)
	{};
};

// try something a little bit simpler
template <typename EdgeT, typename VertexT>
struct Edge 
{
	Vertex<EdgeT, VertexT>* startVertex;
	Vertex<EdgeT, VertexT>* endVertex;

	EdgeT data;

	// allow initialization of the data
	template <typename... Ts>
	Edge(Vertex<EdgeT, VertexT>* _startVertex,
		Vertex<EdgeT, VertexT>* _endVertex,
		Ts&&... dataArgs) :
		startVertex(_startVertex),
		endVertex(_endVertex),
		data(this, dataArgs...)
	{
		setVertex(_startVertex, false);
		setVertex(_endVertex, true);
	};

	// explicitly define some other ctors
	/*template <typename... Ts>
	Edge(Vertex<EdgeT, VertexT>&& _startVertex,
		Vertex<EdgeT, VertexT>&& _endVertex,
		Ts&&... dataArgs) :
		startVertex(_startVertex),
		endVertex(_endVertex),
		data(this, dataArgs...)
	{
		setVertex(_startVertex, false);
		setVertex(_endVertex, true);
	};

	Edge(Vertex<EdgeT, VertexT>&& _startVertex,
		Vertex<EdgeT, VertexT>&& _endVertex) :
		startVertex(_startVertex),
		endVertex(_endVertex),
		data(this)
	{
		setVertex(_startVertex, false);
		setVertex(_endVertex, true);
	};*/

	// really, this shouldn't get called
	template <typename... Ts>
	Edge(Edge&& rhs) : 
		startVertex(rhs.startVertex), endVertex(rhs.endVertex), data(rhs.data) 
	{
		assert(false);
	};

	~Edge() {
		
		if (startVertex != nullptr)
			startVertex->removeEdge(this);

		if (endVertex != nullptr)
			endVertex->removeEdge(this);
	};

private:

	friend struct Vertex<EdgeT, VertexT>;
	
	// store the start and end indices for constant time removal
	size_t startIndex;
	size_t endIndex;

	void setVertex(Vertex<EdgeT, VertexT>* vertex, bool end) {
		
		// after pushing back the size can't be 0 so this is safe
		vertex->edges.push_back(this);
		if (end)
			startIndex = vertex->edges.size() - 1;
		else
			endIndex = vertex->edges.size() - 1;
	}
};


template <typename EdgeT, typename VertexT>
struct Vertex
{
	using Edges = std::vector<Edge<EdgeT, VertexT>*>;

	Edges edges;
	VertexT data;

	// allow initialization of the data
	template <typename... Ts>
	Vertex(Ts&&... dataArgs) :
		edges(),
		data(this, dataArgs...)
	{
	};

	// explicitly define some other ctors to make sure resolution works
	Vertex() : edges(), data(this) {};
	Vertex(Vertex&& rhs) : edges(rhs.edges), data(rhs.data) {};
	Vertex(Vertex& rhs) : edges(rhs.edges), data(rhs.data) {};

	// delete this node
	~Vertex() {

		auto it = edges.begin();
		while (it < edges.end()) {

			Edge<EdgeT, VertexT>* edge = *it;
			it = edges.erase(it);

			// before deleting it, set it's vertices to nullptr,
			// flagging that it doesn't need to do a linear search
			// to delete itself
			if (edge->startVertex == this)
				edge->startVertex = nullptr;

			if (edge->endVertex == this)
				edge->endVertex = nullptr;

			delete edge;
		}
	};

	bool removeEdge(Edge<EdgeT, VertexT>* edge) {

		if (edge == nullptr)
			return false;

		for (auto it = edges.begin(); it < edges.end(); it++) {

			if (*it == edge) {

				edges.erase(it);
				return true;
			}
		}

		return false;
	}

	friend struct Edge<EdgeT, VertexT>;
};

};
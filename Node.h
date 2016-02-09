#pragma once

#include <SFML/Graphics.hpp>

#include "SimNode.h"

namespace hwgame {

class Node : public sf::Drawable, public sf::Transformable
{
	friend class Wire;

private:

	Node();
	~Node();

public:

	struct Connection {
		Node* node;
		Wire* wire;
		bool wireEnd;
	};
	
	enum class NodeType { EMPTY, REFLECTING, INVERTING, ABSORBING, TRANSFER };

	sf::Vector2f getPosition() const { return this->position; }
	void setPosition(sf::Vector2f _position) { this->position = _position; }

private:

	// pointer to the corresponding simulation node
	hwsim::SimNode* simNode;

	// what kind of node are we drawing?
	NodeType nodeType;

	// the position of this node, in game coords (not screen space)
	sf::Vector2f position;

	// the wires that are connected to this node, and which end they're connected by
	std::vector<Connection> connectedWires;

	// satisfy sf::Drawable - renders the wire to the screen
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

};
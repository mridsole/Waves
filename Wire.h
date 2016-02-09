#pragma once

#include <functional>

#include <SFML/Graphics.hpp>

#include "SimWire.h"
#include "EventDispatcher.h"
#include "FrameUpdateDispatcher.h"

// namespace for game-simulation interaction
namespace hwgame {

// responsible for drawing a wire
class WireRenderer : public sf::Drawable
{

public:

	enum class RenderState {
		
	};

	WireRenderer() {};
	~WireRenderer() {};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

// responsible for responding to user input (mouse over, etc)
class WireUserInputHandler 
{

public:

	WireUserInputHandler(FrameUpdateDispatcher& _frameUpdateDispatcher);
	~WireUserInputHandler();

	// for sending info back
	

private:

	unsigned int onFrameUpdateEventCallbackID;
	void onFrameUpdateEvent(const FrameUpdateEvent& frameUpdateEvent);

	FrameUpdateDispatcher& frameUpdateDispatcher;
};

// representation of a wire in the game grid
// keeps track of which nodes it's connected to
class Wire : public sf::Drawable
{
	friend class Node;

public:

	Wire(FrameUpdateDispatcher& frameUpdateDispatcher);
	~Wire();

	// disconnect the start or end node

private:

	// responsible for drawing the wire
	WireRenderer wireRenderer;

	// responsible for handlering user input
	WireUserInputHandler userInputHandler;
	
	// references to the nodes connected to this wire
	Node* startNode;
	Node* endNode;
	
	// pointer to the corresponding SimWire
	hwsim::SimWire* simWire;

	// satisfy sf::Drawable - renders the wire to the screen
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

};
#pragma once

#include "EventDispatcher.h"
#include "FrameUpdateDispatcher.h"
#include "SFML/Graphics.hpp"

// interface/lightweight base for things that can be clicked, mouse-overed,
// things like that etc

using namespace hwgame;

class Mouseable {

public:

	struct Event
	{
		enum class Type { DOWN, UP, OVER, LEAVE, CLICK };
		Type type;

		const FrameUpdateEvent& frameUpdateEvent;
		const sf::Event& sfEvent;

		Event(Type type_, const FrameUpdateEvent& frameUpdateEvent_,
			const sf::Event& sfEvent_) :
			type(type_),
			frameUpdateEvent(frameUpdateEvent_),
			sfEvent(sfEvent_)
		{};
	};

	using MouseableEventDispatcher = EventDispatcher<const Event&>;

	Mouseable(FrameUpdateDispatcher& frameUpdateDispatcher_);
	~Mouseable();

	// dispatchers - add callbacks to these
	MouseableEventDispatcher onClick;
	MouseableEventDispatcher onMouseOver;
	MouseableEventDispatcher onMouseLeave;
	MouseableEventDispatcher onMouseDown;
	MouseableEventDispatcher onMouseUp;

	// inheriting classes must provide this!
	virtual bool mouseInside(int mouseX, int mouseY) = 0;

	// current state of the mouse
	bool mouseDown;
	bool mouseOver;
	bool pendingClick;

private:

	// called by the frame dispatcher
	void onFrame(const FrameUpdateEvent&);
	
	FrameUpdateDispatcher& frameUpdateDispatcher;

	// the ID of our frame update callback
	unsigned int onFrameUpdateCallbackID;
};

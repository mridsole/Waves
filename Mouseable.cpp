#include "stdafx.h"
#include "Mouseable.h"

#include "stdio.h"

Mouseable::Mouseable(FrameUpdateDispatcher& frameUpdateDispatcher_) :
	frameUpdateDispatcher(frameUpdateDispatcher_),
	mouseDown(false), mouseOver(false), pendingClick(false)
{
	// add ourselves to the frame update dispatcher
	onFrameUpdateCallbackID = frameUpdateDispatcher.addCallback(
		std::bind(&Mouseable::onFrame, this, std::placeholders::_1));
}

Mouseable::~Mouseable()
{
	// remove ourselves from the frame update dispatcher
	frameUpdateDispatcher.removeCallbackByID(onFrameUpdateCallbackID);
}

void Mouseable::onFrame(const FrameUpdateEvent& frameUpdateEvent) {

	bool mouseDownChanged = false;
	bool mouseOverChecked = false;
	bool mouseOverOld = mouseOver;
	
	for (auto event : frameUpdateEvent.sfEvents) {

		// TODO: check the mouse button codes here
		// (so that we don't fire this on right mouse button etc)
		if (event.type == sf::Event::MouseButtonPressed &&
			!mouseDown && !mouseDownChanged) {

			mouseDown = true;
			mouseDownChanged = true;

			if (mouseOver) {
				
				printf("down!\n");

				// only fire if we're also inside
				MouseableEvent mEvent(
					MouseableEvent::Type::DOWN,
					frameUpdateEvent,
					event);

				onMouseDown.fire(mEvent);

				// start pending for a click
				pendingClick = true;
			}

		} else if (event.type == sf::Event::MouseButtonReleased &&
			mouseDown && !mouseDownChanged) {

			mouseDown = false;
			mouseDownChanged = true;

			// only fire if we're also inside
			if (mouseOver) {

				printf("up!\n");

				MouseableEvent mEvent(
					MouseableEvent::Type::UP,
					frameUpdateEvent,
					event);

				onMouseUp.fire(mEvent);

				// if pending for a click then fire the click event too
				if (pendingClick) {

					printf("click!");

					MouseableEvent mEvent(
						MouseableEvent::Type::CLICK,
						frameUpdateEvent,
						event);

					onClick.fire(mEvent);
				}
			}

			// always reset the pending click
			pendingClick = false;

		} else if (event.type == sf::Event::MouseMoved &&
			!mouseOverChecked) {

			int x = event.mouseMove.x;
			int y = event.mouseMove.y;
			mouseOver = mouseInside(x, y);
			mouseOverChecked = true;

			// fire the right event
			if (mouseOver != mouseOverOld) {

				MouseableEvent mEvent(
					MouseableEvent::Type::OVER,
					frameUpdateEvent,
					event);

				if (mouseOver == true) {

					printf("over!\n");
					mEvent.type = MouseableEvent::Type::OVER;
					onMouseOver.fire(mEvent);

				} else if (mouseOver == false) {
					
					printf("out!\n");
					mEvent.type = MouseableEvent::Type::LEAVE;
					onMouseLeave.fire(mEvent);
				}
			}
		}
	}
}

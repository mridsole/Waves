#pragma once

#include <SFML/Graphics.hpp>

#include "EventDispatcher.h"

#include "imgui/imgui.h"
#include "imgui/imgui-events-SFML.h"
#include "imgui/imgui-rendering-SFML.h"

namespace hwgui {

// anything prefixed with GUI is 'stateless' in a sense - uses direct
// data binding (const <x>*) and callbacks for data transfer
class GUISimControlsWindow
{

public:
	
	// callbacks
	struct Event {


	};

	// state binding
	struct State {

		bool* simHasStarted;
		bool* simIsRunning;
		float* timeElapsed;
		float* simSpeed;
		bool* enableBreakpoint;
		float* stopAt;

		// default constructor - set everything null
		State() {

			this->simHasStarted = nullptr;
			this->simIsRunning = nullptr;
			this->timeElapsed = nullptr;
			this->simSpeed = nullptr;
			this->enableBreakpoint = nullptr;
			this->stopAt = nullptr;
		}
	};

	GUISimControlsWindow();
	virtual ~GUISimControlsWindow();

	virtual void drawGUI(const sf::Vector2u& windowSize);

	// no point in encapsulating these
	ImColor offlineColor;
	ImColor onlineColor;
	ImColor pausedColor;

	// actual use
	State state;

	// callback dispatchers (for buttons etc)
	EventDispatcher<void(const State&)> startBtnClickDispatcher;
	EventDispatcher<void(const State&)> stopBtnClickDispatcher;

private:

	char* playButtonLabel;

	

	// JUST FOR TESTING - no state like this allowed in actual use
	bool simHasStarted;
	bool simIsRunning;

	float timeElapsed;
};

};
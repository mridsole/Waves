#pragma once

#include "stdio.h"
#include <functional>

#include <SFML/Graphics.hpp>

#include "EventDispatcher.h"
#include "FrameUpdateDispatcher.h"

#include "imgui/imgui.h"
#include "imgui/imgui-events-SFML.h"
#include "imgui/imgui-rendering-SFML.h"

// basically the entry point for the program
class HeatWave
{

public:

	HeatWave();
	~HeatWave();

	// we need a frame update dispatcher to do much here
	hwgame::FrameUpdateDispatcher frameUpdateDispatcher;

	// our sfml render window
	sf::RenderWindow window;

	// begin the game
	void start();

private:
	
	void initializeSFML();
	void initializeIMGUI();

	void gameLoop();

	int pollWindowEvents(std::vector<sf::Event>& events);

	// for efficiency
	hwgame::FrameUpdateEvent frameUpdateEvent;
};


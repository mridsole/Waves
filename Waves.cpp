// RocketSurgery.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Desktop.hpp>

int i = 0;

void onButtonClick() {
	i++;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Beep Bop");
	sf::CircleShape shape = sf::CircleShape(100.f);
	shape.setFillColor(sf::Color::Green);

	// our sfgui object
	sfg::SFGUI sfgui;

	// do button stuff
	auto button = sfg::Button::Create("Hello");

	// registering a callback!
	button->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&onButtonClick));
	
	auto sfgWindow = sfg::Window::Create();
	sfgWindow->SetTitle("An Example");
	sfgWindow->Add(button);

	sfg::Desktop sfgDesktop;
	sfgDesktop.Add(sfgWindow);

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// we have to delegate SFML events to SFGUI
			sfgDesktop.HandleEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		sfgDesktop.Update(1.0f);

		window.clear();
		window.draw(shape);
		sfgui.Display(window);
		window.display();
	}

	return 0;
}

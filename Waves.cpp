// RocketSurgery.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "SimController.h"
#include "SimWire.h"
#include "SimNode.h"

int i = 0;

// boo
void onButtonClick() {
	i++;
}

int main()
{
	// simulation configuration parameters
	sim::SimConfig simCtrlConfig;
	simCtrlConfig.dt = 0.01f;

	// set wire configuration defaults
	simCtrlConfig.defaultWireConfig.dx = 0.01f;
	simCtrlConfig.defaultWireConfig.nx = 100;
	simCtrlConfig.defaultWireConfig.storeTimesteps = 4;

	// set wire property constant initialization defaults
	simCtrlConfig.defaultConstInit.wave = 0.f;
	simCtrlConfig.defaultConstInit.heat = 0.f;
	simCtrlConfig.defaultConstInit.waveSpeed =0.1f;
	simCtrlConfig.defaultConstInit.damping = 0.1f;
	simCtrlConfig.defaultConstInit.diffusivity = 0.005f;

	// a simulation controller
	sim::SimController* simCtrl = new sim::SimController(simCtrlConfig);

	// make a wave, with default initialization
	sim::SimWire* wire = simCtrl->createConfigWire();

	// add some nodes
	sim::SimNode* node1 = simCtrl->createNode();
	sim::SimNode* node2 = simCtrl->createNode();

	// set the nodes at the wire ends
	wire->setBoundaryNode(node1, sim::WireEnd::START);
	wire->setBoundaryNode(node2, sim::WireEnd::END);

	// initialize with the default constant values
	simCtrl->initToDefaultConstants(wire);

	// run a few updates
	//for (unsigned i = 0; i < 20; i++) {
	//	simCtrl->update();
	//}

	// we really need some kind of plotting method 
	// to test the validity of this

	unsigned int nx = simCtrlConfig.defaultWireConfig.nx;

	// create arrays for the wave and heat plots
	sf::VertexArray wavePlot = sf::VertexArray(sf::LinesStrip, nx);
	sf::VertexArray heatPlot = sf::VertexArray(sf::LinesStrip, nx);

	// fill vertices
	for (unsigned i = 0; i < simCtrlConfig.defaultWireConfig.nx; i++) {

		wavePlot[i].position = sf::Vector2f(i * 800.f / nx, 400.f);
		wavePlot[i].color = sf::Color(0, 0, 0, 255u);
		heatPlot[i].position = sf::Vector2f(i * 800.f / nx, 400.f);
		heatPlot[i].color = sf::Color(255u, 0, 0, 255u);
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "Beep Bop");
	sf::CircleShape shape = sf::CircleShape(100.f);
	shape.setFillColor(sf::Color::Green);

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		// run simulation
		for (unsigned i = 0; i < 5; i++) {
		
			simCtrl->update();
		}

		// the sim data
		std::vector<float> waveData = wire->getWave();
		std::vector<float> heatData = wire->getHeat();

		// visualise
		for (unsigned i = 0; i < nx; i++) {
			wavePlot[i].position.y = 300.f - 100.f * waveData[i];
			heatPlot[i].position.y = 300.f - 100.f * heatData[i];
		}

		window.clear(sf::Color(255, 255, 255, 255));
		window.draw(wavePlot);
		window.draw(heatPlot);
		window.display();
	}

	return 0;
}

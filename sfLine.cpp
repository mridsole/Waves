#include "stdafx.h"
#include "VectorOps.h"
#include "sfLine.h"

using namespace hwdraw;

Line::Line() :
	thickness(1.f),
	color(sf::Color::Black),
	startPos(0, 0),
	endPos(0, 0)
{};

Line::~Line()
{};

void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(vertices, 4, sf::Quads);
}

void Line::makeLine() {

	// compute some vectors
	sf::Vector2f dir = endPos - startPos;
	sf::Vector2f unitDir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
	sf::Vector2f unitNorm(-unitDir.y, unitDir.x);
	sf::Vector2f offset = thickness * unitNorm / 2.f;
	
	// set the positions of the vertices
	vertices[0].position = startPos + offset;
	vertices[1].position = endPos + offset;
	vertices[2].position = endPos - offset;
	vertices[3].position = startPos - offset;

	// set the color
	for (unsigned i = 0; i < 4; i++)
		vertices[i].color = color;
}

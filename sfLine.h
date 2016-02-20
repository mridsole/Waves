#pragma once

#include "SFML/Graphics.hpp"

namespace hwdraw {

// TODO: extend for color blending betwen vertices
// a line with thickness, based on rectangle shape
// adapted from SFML wiki
class Line : public sf::Drawable
{
public:
	
	Line();
	~Line();

	// satisfy drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	// recompute the vertices after changing the line properties
	void makeLine();

	float thickness;
	sf::Color color;
	sf::Vector2f startPos;
	sf::Vector2f endPos;

private:

	sf::Vertex vertices[4];
};

};

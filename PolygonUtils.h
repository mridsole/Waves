#pragma once

#include <SFML/Graphics.hpp>

class PolygonUtils
{

public:

	bool pointInPolygon(const sf::VertexArray& vertices, const sf::Vector2f& point);

private:

	// don't instantiate
	PolygonUtils();
	~PolygonUtils();

};



// just implement here
bool PolygonUtils::pointInPolygon(const sf::VertexArray& vertices, const sf::Vector2f& point) {

	bool isInPolygon = false;
	unsigned int nVertices = vertices.getVertexCount();
	unsigned int j = nVertices - 1;

	if (nVertices < 3) { return false; }

	for (unsigned i = 0; i < nVertices; i++) {

		if (vertices[i].position.y < point.y && vertices[j].position.y >= point.y ||
			vertices[i].position.y >= point.y && vertices[j].position.y < point.y) {

			if (vertices[i].position.x + (point.y - vertices[i].position.y) / (vertices[j].position.y -
				vertices[i].position.y) * (vertices[j].position.x - vertices[i].position.x) < point.x) {

				isInPolygon = !isInPolygon;
			}
		}

		j = i;
	}
}
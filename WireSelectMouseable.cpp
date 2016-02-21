#include "stdafx.h"
#include "stdio.h"

#include "WireSelectMouseable.h"
#include "VectorOps.h"
#include "DrawWire.h"

using namespace hwdraw;

WireSelectMouseable::WireSelectMouseable(FrameUpdateDispatcher& fUDispatch,
	DrawWire& drawWire_) :
	Mouseable(fUDispatch),
	maxDistFromLine(5.f),
	drawWire(drawWire_)
{};

WireSelectMouseable::~WireSelectMouseable() 
{};

// TODO: implement this more efficiently
bool WireSelectMouseable::mouseInside(int x, int y) {

	sf::Vector2f unitDir = vec::norm(drawWire.getEndPos() - drawWire.getStartPos());
	sf::Vector2f unitNorm(-unitDir.y, unitDir.x);
	
	sf::Vector2f point((float)x, (float)y);

	// the two corners of interest
	sf::Vector2f leftCorner = drawWire.getStartPos() + maxDistFromLine * unitNorm;
	sf::Vector2f rightCorner = drawWire.getStartPos() - maxDistFromLine * unitNorm;
	sf::Vector2f topRightCorner = drawWire.getEndPos() - maxDistFromLine * unitNorm;
	
	if (vec::cross(leftCorner - point, unitDir) > 0)
		return false;
	if (vec::cross(rightCorner - point, unitDir) < 0)
		return false;
	if (vec::cross(rightCorner - point, unitNorm) > 0)
		return false;
	if (vec::cross(topRightCorner - point, unitNorm) < 0)
		return false;

	return true;
}
	

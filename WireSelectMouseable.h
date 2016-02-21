#pragma once

#include "Mouseable.h"

namespace hwdraw {

class DrawWire;

class WireSelectMouseable : public Mouseable
{
public:

	WireSelectMouseable(FrameUpdateDispatcher& fUDispatch,
		DrawWire& drawWire_);

	~WireSelectMouseable();

	bool mouseInside(int x, int y);

	// distance from the line in screen-space coords
	float maxDistFromLine;
	
	// the wire that this belongs to
	DrawWire& drawWire;
};

};

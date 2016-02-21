#pragma once

#include "Mouseable.h"
#include "FrameUpdateDispatcher.h"

namespace hwgame {
// defines when a click should cause global deselect
class DeselectMouseable : public Mouseable
{
public:

	DeselectMouseable(FrameUpdateDispatcher& fUDispatch);
	~DeselectMouseable();

	// satisfy mouseable
	bool mouseInside(int x, int y);
};

};


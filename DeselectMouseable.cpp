#include "stdafx.h"

#include "DeselectMouseable.h"

DeselectMouseable::DeselectMouseable(FrameUpdateDispatcher& fUDispatch) :
	Mouseable(fUDispatch)
{};

DeselectMouseable::~DeselectMouseable()
{}

bool DeselectMouseable::mouseInside(int x, int y) {
	
	// stub for now -- never deselect!
	return false;
}

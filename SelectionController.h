#pragma once

#include <vector>
#include "Mouseable.h"
#include "Selectable.h"

// controller class for selectables
class SelectionController
{
	friend class Selectable;

public:

	SelectionController(Mouseable& deselectMouseable_);
	~SelectionController();

private:
	
	// called by a selectable when it's been click-selected
	void onClickSelected(Selectable& selectable);

	// when the deselect mouseable is clicked
	void onClickDeselect(const Mouseable::Event& mEvent);
	unsigned int onClickDeselectCallbackID;

	// when this fires, deselect everything
	Mouseable& deselectMouseable;

	// the selectables being controlled
	std::vector<Selectable*> selectables;
};

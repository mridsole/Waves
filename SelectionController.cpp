#include "stdafx.h"
#include <functional>
#include "SelectionController.h"


SelectionController::SelectionController(Mouseable& deselectMouseable_) :
	deselectMouseable(deselectMouseable_)
{
	// etc
	onClickDeselectCallbackID = deselectMouseable.onClick.addCallback(
		std::bind(&SelectionController::onClickDeselect, this, std::placeholders::_1)
		);
}

SelectionController::~SelectionController()
{
	// remove the click deselect callback
	deselectMouseable.onClick.removeCallbackByID(onClickDeselectCallbackID);
}

void SelectionController::onClickSelected(Selectable& selectable) {
	
	// deselect all selectables that aren't this one
	for (auto sel : selectables) {
		if (sel != &selectable && sel->state != Selectable::State::DEFAULT) {
			sel->deselect();
		}
	}
	
	// if this isn't already selected, select it
	if (selectable.state != Selectable::State::SELECTED) {
		selectable.select();
	}
}

void SelectionController::onClickDeselect(const Mouseable::Event& mEvent) {
	
	// deselect all selectables
	for (auto sel : selectables)
		sel->deselect();
}

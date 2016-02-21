#include "stdafx.h"

#include "Selectable.h"
#include "SelectionController.h"

Selectable::Selectable(SelectionController& selCtrl_, 
	Mouseable& mouseable_) :
	selCtrl(selCtrl_),
	mouseable(mouseable_),
	state(State::DEFAULT)
{
	// add ourselves to the selection controller
	selCtrl.selectables.push_back(this);

	// bind our function to the mouseable's click dispatcher
	onClickCallbackID = mouseable.onClick.addCallback(
		std::bind(&Selectable::onClick, this, std::placeholders::_1));
}

Selectable::~Selectable()
{
	// remove ourselves from the selection controller
	auto& sels = selCtrl.selectables;
	for (auto it = sels.begin(); it < sels.end(); it++) {
		if (*it == this) {
			sels.erase(it);
			break;
		}
	}

	// remove our registered onClick callback
	mouseable.onClick.removeCallbackByID(onClickCallbackID);
}

void Selectable::select() {

	state = State::SELECTED;

	Event selEvent(Event::Type::SELECTED, *this);
	onSelect.fire(selEvent);
}

void Selectable::deselect() {
	
	if (state == State::DEFAULT)
		return;

	state = State::DEFAULT;

	Event selEvent(Event::Type::DESELECTED, *this);
	onDeselect.fire(selEvent);
}

void Selectable::onClick(const Mouseable::Event& mEvent) {

	// if this is already selected, then don't do anything
	if (state == State::SELECTED)
		return;

	// otherwise, flag as selected and notify the selCtrl
	selCtrl.onClickSelected(*this);
}

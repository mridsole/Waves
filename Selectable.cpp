#include "stdafx.h"

#include "Selectable.h"
#include "SelectionController.h"

Selectable::Selectable(SelectionController& selCtrl_, 
	Mouseable& mouseable_) :
	selCtrl(selCtrl_),
	mouseable(mouseable_),
	state(State::DEFAULT)
{
	// bind our function to the mouseable's click dispatcher
	onClickCallbackID = mouseable.onClick.addCallback(
		std::bind(&Selectable::onClick, this, std::placeholders::_1));
}

Selectable::~Selectable()
{
	// remove our registered onClick callback
	mouseable.onClick.removeCallbackByID(onClickCallbackID);
}

void Selectable::select() {

	if (state == State::SELECTED)
		return;

	state = State::SELECTED;

	Event selEvent(Event::Type::SELECTED, *this);
	onSelectDispatcher.fire(selEvent);
}

void Selectable::deselect() {
	
	if (state == State::DEFAULT)
		return;

	state = State::DEFAULT;

	Event selEvent(Event::Type::DESELECTED, *this);
	onDeselectDispatcher.fire(selEvent);
}

void Selectable::onClick(const Mouseable::Event& mEvent) {

	// if this is already selected, then don't do anything
	if (state == State::SELECTED)
		return;

	// otherwise, flag as selected and notify the selCtrl
	state = State::SELECTED;
	selCtrl.onClickSelected(*this);
}

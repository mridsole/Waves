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

	onMouseOverCallbackID = mouseable.onMouseOver.addCallback(
		std::bind(&Selectable::onMouseOver, this, std::placeholders::_1));

	onMouseLeaveCallbackID = mouseable.onMouseLeave.addCallback(
		std::bind(&Selectable::onMouseLeave, this, std::placeholders::_1));
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

void Selectable::onMouseOver(const Mouseable::Event& mEvent) {
	
	// don't change state if we're selected
	if (state == Selectable::State::DEFAULT)
		state = Selectable::State::HOVER;

	Event selEvent(Event::Type::HOVER, *this);
	onHover.fire(selEvent);
}

void Selectable::onMouseLeave(const Mouseable::Event& mEvent) {
	
	if (state == Selectable::State::HOVER)
		state = Selectable::State::DEFAULT;
	
	Event selEvent(Event::Type::LEAVE, *this);
	onLeave.fire(selEvent);
}

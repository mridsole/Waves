#pragma once

#include "EventDispatcher.h"
#include "Mouseable.h"

class SelectionController;

// abstract base for things that can be selected with the mouse
class Selectable
{
public:

	// indicates the current UI state
	enum class State { DEFAULT, HOVER, SELECTED };

	// event
	struct Event 
	{
		// the type of event
		enum class Type { SELECTED, DESELECTED };
		
		Type type;
		Selectable& source;
		
		Event(Type type_, Selectable& source_) :
			type(type_),
			source(source_)
		{};
	};

	using SelectableEventDispatcher = EventDispatcher<const Selectable::Event&>;

	Selectable(SelectionController& selCtrl, Mouseable& mouseable);
	~Selectable();

	void select();
	void deselect();

	// event dispatchers for select and unselect
	SelectableEventDispatcher onSelect;
	SelectableEventDispatcher onDeselect;

	State state;

private:

	unsigned int onClickCallbackID;
	void onClick(const Mouseable::Event& mEvent);

	SelectionController& selCtrl;
	Mouseable& mouseable;
};

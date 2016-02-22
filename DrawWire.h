#pragma once

#include "SFML/Graphics.hpp"

#include "sfLine.h"
#include "Mouseable.h"
#include "Selectable.h"
#include "SelectionController.h"
#include "WireSelectMouseable.h"

namespace hwdraw {

// responsible for drawing a game wire to the screen
class DrawWire : public sf::Drawable
{
public:

	DrawWire(SelectionController& selCtrl, 
		FrameUpdateDispatcher& fUDispatch);
	~DrawWire();

	// satisfy drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// satisfy mouseable
	bool mouseInside(int x, int y);

	// get the start/end positions of the wire
	sf::Vector2f getStartPos() const;
	sf::Vector2f getEndPos() const;
	
	// set positions
	void setStartPos(sf::Vector2f pos);
	void setEndPos(sf::Vector2f pos);

	// the mouseable for selecting the wire
	WireSelectMouseable selMouseable;

	// the selectable for this
	Selectable selectable;

private:
	
	unsigned int onSelectCallbackID;
	void onSelect(const Selectable::Event& selEvent);

	unsigned int onDeselectCallbackID;
	void onDeselect(const Selectable::Event& selEvent);

	// the line used to draw this
	Line drawLine;

	// the underline used to indicate that the wire is selected
	Line selectedDrawLine;

	// the underline used for mouse hover
	Line hoverDrawLine;
};

};

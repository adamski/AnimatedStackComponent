/*
  ==============================================================================

    MarginedContainerComponent.h
    Created: 12 Mar 2011 2:17:07pm
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __MARGINEDCONTAINERCOMPONENT_H_B4042581__
#define __MARGINEDCONTAINERCOMPONENT_H_B4042581__

#include "../../JuceLibraryCode/JuceHeader.h"

/** A fairly specialised type of Component. This has a main body component, and
	optionally left and right margin components. The margin sizes can be set manually,
	and the body component always fills what space is left. It's useful for header
	components, or ListBox items, as it allows some piece of content to be supplemented
	by widgets at either side - scaling to fit automatically. 
*/
class MarginedContainerComponent	:	public Component
{
public:

	MarginedContainerComponent ();
	virtual ~MarginedContainerComponent ();

	void clearLeftMargin (bool deleteChildren = true);
	void clearRightMargin (bool deleteChildren = true);
	void setLeftMarginContent (Component* content, int width, const BorderSize<int> padding = BorderSize<int>(0));
	void setRightMarginContent (Component* content, int width, const BorderSize<int> padding = BorderSize<int>(0));

	void setLeftMarginWidth (int width);
	void setRightMarginWidth (int width);
	int getLeftMarginWidth () const;
	int getRightMarginWidth () const;
	int getBodyWidth () const;

	void resized ();

	Component& getLeftMargin ();
	Component& getRightMargin ();
	Component& getBody ();

	MarkerList* getMarkers (bool xAxis);

private:

	Component leftMargin;
	Component body;
	Component rightMargin;
	MarkerList xMarkers;

};



#endif  // __MARGINEDCONTAINERCOMPONENT_H_B4042581__

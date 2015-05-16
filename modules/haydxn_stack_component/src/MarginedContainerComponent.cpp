/*
  ==============================================================================

    MarginedContainerComponent.cpp
    Created: 12 Mar 2011 2:17:07pm
    Author:  Haydxn

  ==============================================================================
*/

#include "MarginedContainerComponent.h"

namespace MarginedContainerHelpers
{
	static const char* leftMarginMarker = "LMarginMarker";
	static const char* rightMarginMarker = "RMarginMarker";
};

using namespace juce;

MarginedContainerComponent::MarginedContainerComponent ()
{
	setInterceptsMouseClicks (false,true);

	addAndMakeVisible (&leftMargin);
	addAndMakeVisible (&rightMargin);
	addAndMakeVisible (&body);

	xMarkers.setMarker (MarginedContainerHelpers::leftMarginMarker, RelativeCoordinate(0));
	xMarkers.setMarker (MarginedContainerHelpers::rightMarginMarker, RelativeCoordinate("parent.width"));

	String leftBounds;
	leftBounds << "0,0," << MarginedContainerHelpers::leftMarginMarker << ",parent.height";
	leftMargin.setBounds (leftBounds);
	leftMargin.setComponentID("Left");

	String rightBounds;
	rightBounds << MarginedContainerHelpers::rightMarginMarker << ",0,parent.width,parent.height";
	rightMargin.setBounds (rightBounds);
	rightMargin.setComponentID("Right");

	String bodyBounds;
	bodyBounds << MarginedContainerHelpers::leftMarginMarker << ",0,"
		<< MarginedContainerHelpers::rightMarginMarker << ",parent.height";
	body.setBounds (bodyBounds);
	body.setComponentID("Body");

	body.setInterceptsMouseClicks (false,true);
	leftMargin.setInterceptsMouseClicks (false,true);
	rightMargin.setInterceptsMouseClicks (false,true);

}

MarginedContainerComponent::~MarginedContainerComponent ()
{
	removeChildComponent (&leftMargin);
	removeChildComponent (&rightMargin);
	removeChildComponent (&body);
}

void MarginedContainerComponent::resized ()
{
}

void MarginedContainerComponent::clearLeftMargin (bool deleteChildren)
{
	setLeftMarginWidth (0);

	if (deleteChildren)
		leftMargin.deleteAllChildren ();
	else leftMargin.removeAllChildren ();
}

void MarginedContainerComponent::clearRightMargin (bool deleteChildren)
{
	setRightMarginWidth (0);

	if (deleteChildren)
		rightMargin.deleteAllChildren ();
	else rightMargin.removeAllChildren ();
}

void MarginedContainerComponent::setLeftMarginContent (Component* content, int width, const BorderSize<int> padding)
{
	leftMargin.addAndMakeVisible (content);
	String bounds;
	bounds 
		<< padding.getLeft() << "," 
		<< padding.getTop() << ","
		<< "parent.width-" << padding.getRight() << ","
		<< "parent.height-" << padding.getBottom();
	content->setBounds (bounds);
	setLeftMarginWidth (width + padding.getLeftAndRight());
}

void MarginedContainerComponent::setRightMarginContent (Component* content, int width, const BorderSize<int> padding)
{
	rightMargin.addAndMakeVisible (content);
	String bounds;
	bounds 
		<< padding.getLeft() << "," 
		<< padding.getTop() << ","
		<< "parent.width-" << padding.getRight() << ","
		<< "parent.height-" << padding.getBottom();
	content->setBounds (bounds);
	setRightMarginWidth (width + padding.getLeftAndRight());
}

void MarginedContainerComponent::setLeftMarginWidth (int width)
{
	xMarkers.setMarker (MarginedContainerHelpers::leftMarginMarker, RelativeCoordinate(width));
}

void MarginedContainerComponent::setRightMarginWidth (int width)
{
	String markerPos;
	markerPos << "parent.width-" << String(width);
	xMarkers.setMarker (MarginedContainerHelpers::rightMarginMarker, RelativeCoordinate(markerPos));
}

int MarginedContainerComponent::getLeftMarginWidth () const
{
	return leftMargin.getWidth();
}

int MarginedContainerComponent::getRightMarginWidth () const
{
	return rightMargin.getWidth();
}

int MarginedContainerComponent::getBodyWidth () const
{
	return body.getWidth();
}

Component& MarginedContainerComponent::getLeftMargin ()
{
	return leftMargin;
}

Component& MarginedContainerComponent::getRightMargin ()
{
	return rightMargin;
}

Component& MarginedContainerComponent::getBody ()
{
	return body;
}

MarkerList* MarginedContainerComponent::getMarkers (bool xAxis)
{
	return (xAxis ? &xMarkers : 0);
}

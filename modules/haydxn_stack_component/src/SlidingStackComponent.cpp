/*
  ==============================================================================

    SlidingStackComponent.cpp
    Created: 12 Mar 2011 12:13:09pm
    Author:  Haydxn

  ==============================================================================
*/

#include "SlidingStackComponent.h"

using namespace juce;

SlidingStackComponent::SlidingStackComponent ()
:	slideDuration (150),
	startSpeed (1.0),
	endSpeed (1.0)
{
}

SlidingStackComponent::~SlidingStackComponent ()
{
}

void SlidingStackComponent::refreshLayout ()
{
	for (int i=0; i<getStackSize (); i++)
	{
		Component* panel = getContentComponentAtIndex (i);
		if (i == getStackFocusIndex())
		{
			panel->setVisible (true);
			panel->setBounds (0,0,getWidth(),getHeight());
		}
		else
		{
			panel->setVisible (false);
		}
	}
}

void SlidingStackComponent::setSlideDuration (int durationMs, double startSpeed_, double endSpeed_)
{
	slideDuration = durationMs;
	startSpeed = startSpeed_;
	endSpeed = endSpeed_;
}

void SlidingStackComponent::handleContentComponentAdded (Component* newContent, int index, bool animate)
{
	addAndMakeVisible (newContent);
	newContent->setBounds (getBoundsForContent(index));
}

void SlidingStackComponent::handleContentComponentRemoved (Component* contentRemoved, int index, bool animate)
{
	if (animate)
	{
		Desktop::getInstance().getAnimator().fadeOut (contentRemoved, 200);
		removeChildComponent (contentRemoved);
		if (shouldContentComponentBeDeleted(contentRemoved))
			delete contentRemoved;
	}
	else
	{
		removeChildComponent (contentRemoved);
		if (shouldContentComponentBeDeleted(contentRemoved))
			delete contentRemoved;
	}
}

void SlidingStackComponent::handleStackFocusChange (Component* newFocusContent, int newIndex, int oldIndex, bool animate)
{
	if (!animate)
	{
		refreshLayout();
		return;
	}

	Component* panel;

	int w = getWidth ();
	int h = getHeight ();

	Rectangle<int> bounds (0,0,w,h);

	// Move the old panel...
	panel = getContentComponentAtIndex (oldIndex);
	if (panel != 0)
	{
		panel->setVisible (true);

		// Make sure the panel is currently on-screen to exit...
		bounds.setX (0);
		panel->setBounds (bounds);

		// Animate it to exit
		bounds.setX ((oldIndex < newIndex) ? -w : w);
		Desktop::getInstance().getAnimator().animateComponent(panel, bounds, 1.0f, slideDuration, true, startSpeed, endSpeed);
	}

	// Move the new panel...
	panel = getContentComponentAtIndex (newIndex);
	if (panel != 0)
	{
		panel->setVisible (true);

		// Place the panel in a suitable position for entry...
		bounds.setX ((newIndex < oldIndex) ? -w : w);
		panel->setBounds (bounds);

		// Animate it to enter and fill the bounds.
		bounds.setX (0);
		Desktop::getInstance().getAnimator().animateComponent(panel, bounds, 1.0f, slideDuration, true, startSpeed, endSpeed);
	}
}

Rectangle<int> SlidingStackComponent::getBoundsForContent (int index)
{
	int w = getWidth ();
	int h = getHeight ();
	int x = (index-getStackFocusIndex()) * w;
	Rectangle<int> rect (x,0,w,h);
	return rect;
}

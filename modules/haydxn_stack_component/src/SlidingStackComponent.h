/*
  ==============================================================================

    SlidingStackComponent.h
    Created: 12 Mar 2011 12:13:09pm
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __SLIDINGSTACKCOMPONENT_H_3EB614FF__
#define __SLIDINGSTACKCOMPONENT_H_3EB614FF__


class SlidingStackComponent	:	public StackComponent
{
public:

	SlidingStackComponent ();
	virtual ~SlidingStackComponent ();

protected:

	void setSlideDuration (int durationMs, double startSpeed = 1.0, double endSpeed = 1.0);

	virtual void refreshLayout ();
	virtual void handleContentComponentAdded (juce::Component* newContent, int index, bool animate);
	virtual void handleContentComponentRemoved (juce::Component* contentRemoved, int index, bool animate);
	virtual void handleStackFocusChange (juce::Component* newFocusContent, int newIndex, int oldIndex, bool animate);

    juce::Rectangle<int> getBoundsForContent (int index);

private:

	int slideDuration;
	double startSpeed;
	double endSpeed;

};



#endif  // __SLIDINGSTACKCOMPONENT_H_3EB614FF__

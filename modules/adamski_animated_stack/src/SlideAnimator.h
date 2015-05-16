/*
  ==============================================================================

    SlideAnimator.h
    Created: 4 May 2015 10:40:25pm
    Author:  Adam Elemental

  ==============================================================================
*/

#ifndef SLIDEANIMATOR_H_INCLUDED
#define SLIDEANIMATOR_H_INCLUDED

using namespace juce;

class SlideAnimator : public StackAnimator 
{
public:

    SlideAnimator ();
    SlideAnimator (int slideDuration, float startSpeed, float endSpeed);

    void refreshLayout ();
    void animateContentComponentAdded (Component *newContent, int index);
    void animateContentComponentRemoved (Component* contentRemoved, int index);
    void animateStackFocusChange (Component* newFocusContent, int newIndex, int oldIndex);
    void setSlideDuration (int durationMs, double newStartSpeed, double newEndSpeed);

private:

    Rectangle<int> getBoundsForContent (int index);

    int slideDuration;
    double startSpeed;
    double endSpeed;


};



#endif  // SLIDEANIMATOR_H_INCLUDED

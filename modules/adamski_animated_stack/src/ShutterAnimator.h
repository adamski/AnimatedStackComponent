/*
  ==============================================================================

    ShutterAnimator.h
    Created: 4 May 2015 10:40:25pm
    Author:  Adam Wilson

  ==============================================================================
*/

#ifndef SHUTTERANIMATOR_H_INCLUDED
#define SHUTTERANIMATOR_H_INCLUDED


class ShutterAnimator : public StackAnimator, public juce::ChangeListener
{
public:

    ShutterAnimator (juce::Rectangle<int> focusArea);
    ShutterAnimator (juce::Rectangle<int> focusArea, int slideDuration, float startSpeed, float endSpeed);
    ShutterAnimator ();
    ShutterAnimator (int slideDuration, float startSpeed, float endSpeed);

    ~ShutterAnimator ();
    
    void setFocusArea (juce::Rectangle<int> newFocusArea);

    void refreshLayout ();
    void animateContentComponentAdded (juce::Component *newContent, int index);
 
    /**
     * save the image of the deleted component and display that
     * so that the animation can play on top of it
     */
    void animateContentComponentRemoved (juce::Component* contentRemoved, int index);
    
    void animateStackFocusChange (juce::Component* newFocusContent, int newIndex, int oldIndex);
    void setDuration (int durationMs, double newStartSpeed, double newEndSpeed);

private:

    /**
     * Implement ChangeListener
     * Check if we've finished an animation and remove the proxy image components 
     * plus other stuff to make it work both for back button and breadcrumb navigation
     */
    void changeListenerCallback (juce::ChangeBroadcaster *source);

    /** 
     * Get current bounds for the StackComponent
     */
    juce::Rectangle<int> getCurrentBounds() const;

    int slideDuration;
    double startSpeed;
    double endSpeed;
    bool finishedAnimating = false;
    bool isOpening;

    juce::ScopedPointer<juce::ImageComponent> topSnapshot;
    juce::ScopedPointer<juce::ImageComponent> bottomSnapshot;
    juce::ScopedPointer<juce::ImageComponent> focusSnapshot;
    juce::ScopedPointer<juce::ImageComponent> deletedPanel;
    juce::Component::SafePointer<juce::Component> previousPanel;

    juce::Rectangle<int> focusArea;

};

#endif  // SHUTTERANIMATOR_H_INCLUDED

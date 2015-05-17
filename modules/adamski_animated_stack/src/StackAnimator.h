/*
  ==============================================================================

    StackAnimator.h
    Created: 4 May 2015 8:52:18pm
    Author:  Adam Wilson

  ==============================================================================
*/

#ifndef STACKANIMATOR_H_INCLUDED
#define STACKANIMATOR_H_INCLUDED

class StackAnimator : public juce::ReferenceCountedObject
{
public:
    typedef juce::ReferenceCountedObjectPtr<StackAnimator> Ptr;

    StackAnimator ();
    //virtual ~StackAnimator() {};
    
    virtual void animateContentComponentAdded (juce::Component* newContent, int index) = 0;
    virtual void animateContentComponentRemoved (juce::Component* contentRemoved, int index) = 0;
    virtual void animateStackFocusChange (juce::Component* newFocusContent, int newIndex, int oldIndex) = 0;
    virtual void refreshLayout() = 0;

    void setStackComponent(StackComponent* stack);

protected:
    juce::ScopedPointer<StackComponent> stackComponent;
};
    


#endif  // STACKANIMATOR_H_INCLUDED

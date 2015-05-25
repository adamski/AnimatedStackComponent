/*
  ==============================================================================

    DefaultStackAnimator.h
    Created: 4 May 2015 8:52:18pm
    Author:  Adam Wilson

  ==============================================================================
*/

#ifndef DEFAULTSTACKANIMATOR_H_INCLUDED
#define DEFAULTSTACKANIMATOR_H_INCLUDED

class DefaultStackAnimator : public StackAnimator
{
public:
    typedef juce::ReferenceCountedObjectPtr<DefaultStackAnimator> Ptr;

    DefaultStackAnimator () {}
    //virtual ~DefaultStackAnimator() {};
    
    void animateContentComponentAdded (juce::Component* newContent, int index) 
    {}
    void animateContentComponentRemoved (juce::Component* contentRemoved, int index) 
    {}
    void animateStackFocusChange (juce::Component* newFocusContent, int newIndex, int oldIndex) 
    {}
    
    void refreshLayout()
    {
        stackComponent->refreshLayout();
    }

};
    


#endif  // DEFAULTSTACKANIMATOR_H_INCLUDED

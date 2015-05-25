/*
  ==============================================================================

    StackAnimator.cpp
    Created: 4 May 2015 8:52:18pm
    Author:  Adam Wilson

  ==============================================================================
*/


StackAnimator::StackAnimator () {}
    
void StackAnimator::animateContentComponentAdded (juce::Component* newContent, int index) {}
void StackAnimator::animateContentComponentRemoved (juce::Component* contentRemoved, int index) {}
void StackAnimator::animateStackFocusChange (juce::Component* newFocusContent, int newIndex, int oldIndex) {}

void StackAnimator::refreshLayout() 
{
    jassert (stackComponent != nullptr);
}

void StackAnimator::setStackComponent(AnimatedStackComponent* stack)
{
    stackComponent = stack;
}

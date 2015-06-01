/*
  ==============================================================================

    AnimatedStackComponent.h
    Created: 14 May 2015 12:13:09pm
    Author:  Adam Wilson

  ==============================================================================
*/

#ifndef __ANIMATEDSTACKCOMPONENT_H_INCLUDED
#define __ANIMATEDSTACKCOMPONENT_H_INCLUDED

#include "StackAnimator.h"

namespace AnimatedStackHelpers
{
    static const juce::Identifier stackAnimatorId ("StackAnimator");

    static void setStackAnimatorForComponent (StackAnimator::Ptr stackAnimator, juce::Component *component)
    {
        component->getProperties().set (AnimatedStackHelpers::stackAnimatorId, juce::var(stackAnimator));
        stackAnimator->incReferenceCount(); // this prevents a crash when using 'Back' button on this component
    }

    static StackAnimator::Ptr getStackAnimatorForComponent (juce::Component *component)
    {
        juce::var* animatorVar = component->getProperties().getVarPointer (AnimatedStackHelpers::stackAnimatorId);
        return dynamic_cast<StackAnimator*> (animatorVar->getObject());
    }
};

class AnimatedStackComponent	:	public StackComponent
{
    friend class DefaultStackAnimator;

    public:

        AnimatedStackComponent (const StackAnimator::Ptr & defaultStackAnimator);
        AnimatedStackComponent ();
        ~AnimatedStackComponent ();

        void setDefaultStackAnimator(const StackAnimator::Ptr & defaultStackAnimator);

    protected:

        virtual void handleContentComponentAdded (juce::Component* newContent, int index, bool animate);
        virtual void handleContentComponentRemoved (juce::Component* contentRemoved, int index, bool animate);
        virtual void handleStackFocusChange (juce::Component* newFocusContent, int newIndex, int oldIndex, bool animate);

        StackAnimator::Ptr getStackAnimatorForComponent (juce::Component* component);
        StackAnimator::Ptr getStackAnimator();

    private:
        StackAnimator::Ptr stackAnimator;
};



#endif  // __ANIMATEDSTACKCOMPONENT_H_INCLUDED

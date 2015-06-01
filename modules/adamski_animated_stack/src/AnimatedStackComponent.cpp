/*
    ==============================================================================

    AnimatedStackComponent.cpp
    Created: 12 Mar 2011 12:13:09pm
    Author:  Haydxn

    ==============================================================================
*/

class DefaultStackAnimator;

AnimatedStackComponent::AnimatedStackComponent (const StackAnimator::Ptr & defaultStackAnimator) 
    :   StackComponent(), 
        stackAnimator (defaultStackAnimator)
{
    stackAnimator->setStackComponent (this);
}

AnimatedStackComponent::AnimatedStackComponent () 
    :   StackComponent()
{
    stackAnimator = new DefaultStackAnimator(); 
    stackAnimator->setStackComponent (this);
}

AnimatedStackComponent::~AnimatedStackComponent ()
{
    // stackAnimator->decReferenceCount();
}

void AnimatedStackComponent::setDefaultStackAnimator(const StackAnimator::Ptr & defaultStackAnimator)
{
    stackAnimator = defaultStackAnimator;
}

// void AnimatedStackComponent::push (juce::Component* contentComponent, bool shouldBeDeleted, bool autoFocus, bool animate) 
// {
//     if (stackAnimator.get() == nullptr) animate = false;
//     StackComponent::push (contentComponent, shouldBeDeleted, autoFocus, animate);
// }


void AnimatedStackComponent::handleContentComponentAdded (Component* newContent, int index, bool animate)
{
    addAndMakeVisible (newContent);

    if (animate) 
    {
        stackAnimator->animateContentComponentAdded (newContent, index);
    }

}

void AnimatedStackComponent::handleContentComponentRemoved (Component* contentRemoved, int index, bool animate)
{
    if (animate)
    {
        getStackAnimatorForComponent (contentRemoved)->animateContentComponentRemoved (contentRemoved, index);
    }
    
    removeChildComponent (contentRemoved);
    if (shouldContentComponentBeDeleted(contentRemoved))
        delete contentRemoved;
}

void AnimatedStackComponent::handleStackFocusChange (Component* newFocusContent, int newIndex, int oldIndex, bool animate)
{
    if (! animate )
    {
        getStackAnimatorForComponent (newFocusContent)->refreshLayout();
    }
    else 
    {
        DBG ("newIndex: " << newIndex << ", oldIndex: " << oldIndex);
        if (newIndex < oldIndex)  // if we're going backwards
            newFocusContent = getContentComponentAtIndex(oldIndex); // set the newFocusContent to the previous component
        getStackAnimatorForComponent (newFocusContent)->animateStackFocusChange (newFocusContent, newIndex, oldIndex);
    }
}

StackAnimator::Ptr AnimatedStackComponent::getStackAnimatorForComponent (Component *component) 
{
    NamedValueSet & properties = component->getProperties();
    if (properties.contains (AnimatedStackHelpers::stackAnimatorId)) // also check for valid stackAnimator object
    {
        return AnimatedStackHelpers::getStackAnimatorForComponent (component);
    }
    else
    {
        return getStackAnimator();  
    }
}

StackAnimator::Ptr AnimatedStackComponent::getStackAnimator() 
{
    return stackAnimator;
}


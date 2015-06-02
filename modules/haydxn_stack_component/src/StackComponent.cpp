/*
    ==============================================================================

    StackComponent.cpp
   
    Created: 5 Mar 2011 1:20:56pm
    Author:  Haydxn

    ==============================================================================
*/

StackComponent::StackComponent ()
:	stackFocusIndex (0),
    popAutoFocusOrder (autoFocusBeforeContentChange)
{

}


StackComponent::~StackComponent ()
{
    clearStack (false);
}


void StackComponent::push (Component* contentComponent, bool shouldBeDeleted, bool autoFocus, bool animate)
{
    if (contentComponent)
    {
        jassert (contentComponent != nullptr);
        // The component you are pushing already exists in the stack
        jassert (!contentComps.contains(contentComponent));

        int newIndex = contentComps.size ();
        contentComps.add (contentComponent);

        if (shouldBeDeleted)
            contentComponent->getProperties().set (StackComponentHelpers::deletionFlagId, true);

        handleContentComponentAdded (contentComponent, newIndex, animate);

        stackChanged ();

        if (autoFocus)
            setStackFocusToTop (animate);
    }
}


void StackComponent::pushAfterExisting (Component* existing, Component* contentComponent, bool shouldBeDeleted, bool animate, bool autoFocus)
{
    popComponentsAbove (existing, false, animate);
    push (contentComponent, shouldBeDeleted, autoFocus, animate);
}


void StackComponent::pop (int numberToRemove, bool autoFocus, bool animate)
{
    numberToRemove = jmin (numberToRemove, contentComps.size());

    int newHead = contentComps.size() - (numberToRemove + 1);
    bool anyRemoved = (numberToRemove > 0);
    bool focusShouldChange = (newHead != getStackFocusIndex()) && anyRemoved;

    if (autoFocus && focusShouldChange && (popAutoFocusOrder == autoFocusBeforeContentChange))
        setStackFocusIndex (newHead, animate);

    while (numberToRemove > 0)
    {
        Component* contentToRemove = contentComps.getLast ();
        contentComps.removeLast ();
        int removalIndex = contentComps.size(); // <- last item is no longer there, so size works

        if (contentToRemove != nullptr) // added to prevent bad access error on NULL contentToRemove
            handleContentComponentRemoved (contentToRemove, removalIndex, animate);
        
        --numberToRemove;
    }

    if (anyRemoved)
    {
        stackChanged ();
    }

    if (autoFocus && focusShouldChange && (popAutoFocusOrder == autoFocusAfterContentChange))
        setStackFocusIndex (newHead, animate);
}


void StackComponent::popComponentsAbove (Component* contentComponent, bool autoFocus, bool animate)
{
    popComponentsAboveIndex (indexOfContentComponent (contentComponent), autoFocus, animate);
}


void StackComponent::popComponentsAboveIndex (int contentIndex, bool autoFocus, bool animate)
{
    if (contentIndex > -1)
    {
        int numToRemove = contentComps.size() - (contentIndex + 1);
        pop (numToRemove, autoFocus, animate);
    }
}


void StackComponent::clearStack (bool animate)
{
    pop (contentComps.size(), false, animate);
}


int StackComponent::indexOfContentComponent (Component* componentToFind) const
{
    return contentComps.indexOf (componentToFind);
}


Component* StackComponent::getContentComponentAtIndex (int index) const
{
    return contentComps[index];
}


int StackComponent::getStackSize () const
{
    return contentComps.size ();
}


void StackComponent::setStackFocusIndex (int index, bool animate)
{
    if ((stackFocusIndex != index) && (index < contentComps.size()) && index >= 0)
    {
        int oldFocusIndex = stackFocusIndex;
        stackFocusIndex = index;
        handleStackFocusChange (contentComps[index], index, oldFocusIndex, animate);

        stackFocusChanged ();
    }
}


void StackComponent::setStackFocusRelative (int relativeIndex, bool animate)
{
    int newIndex = stackFocusIndex + relativeIndex;
    if (newIndex >= 0 && newIndex < contentComps.size())
    {
        setStackFocusIndex (newIndex, animate);
    }
}


void StackComponent::setStackFocusContent (Component* contentComponent, bool animate)
{
    int index = contentComps.indexOf (contentComponent);
    setStackFocusIndex (index, animate);
}


void StackComponent::setStackFocusToTop (bool animate)
{
    setStackFocusIndex (contentComps.size()-1, animate);
}


int StackComponent::getStackFocusIndex () const
{
    return stackFocusIndex;
}


Component* StackComponent::getStackFocusContent () const
{
    return contentComps[stackFocusIndex];
}


bool StackComponent::shouldContentComponentBeDeleted (Component* comp)
{
    if (comp != 0)
        return comp->getProperties() [StackComponentHelpers::deletionFlagId];

    return false;
}


void StackComponent::addListener (Listener* listener)
{
    listeners.add (listener);
}


void StackComponent::removeListener (Listener* listener)
{
    listeners.remove (listener);
}


void StackComponent::stackChanged ()
{
    DBG ("StackComponent::stackChanged");
    //BailOutChecker checker (this);
    listeners.call (&StackComponent::Listener::stackComponentContentChanged, this);
}


void StackComponent::stackFocusChanged ()
{
    DBG ("StackComponent::stackFocusChanged");
    listeners.call (&StackComponent::Listener::stackComponentFocusChanged, this);
}


void StackComponent::resized ()
{
    refreshLayout ();
}

StackComponent* StackComponent::findForContent (Component* content)
{
    // NOTE: if we use UtilityProperties, we can guarantee a successful find,
    // by embedding a weak reference to a StackComponent when pushing a content
    // component onto the stack. Otherwise, this will only work if the derived
    // StackComponent subclass actually holds the content within itself as a child
    // (or within some child structure).
    // TBH though, it's probably unlikely anyone would ever bother trying it any
    // other way... but you never know... this comment is left here just in case.
    return content->findParentComponentOfClass<StackComponent> ();
}

void StackComponent::setPopAutoFocusOrder (StackComponent::AutoFocusOrder order)
{
    popAutoFocusOrder = order;
}

void StackComponent::refreshLayout ()
{
    int focusIndex = getStackFocusIndex ();

    for (int i = 0; i<getStackSize(); i++)
    {
        Component* c = getContentComponentAtIndex(i);
        if (i == focusIndex)
        {
            c->setBounds (0,0,getWidth(),getHeight());
            c->setVisible(true);
        }
        else
        {
            c->setVisible(false);
            c->setBounds (0,0,getWidth(),getHeight());
        }
    }
}


void StackComponent::handleContentComponentAdded (Component* newContent, int index, bool animate)
{
    addAndMakeVisible (newContent);
    refreshLayout ();
}


void StackComponent::handleContentComponentRemoved (Component* contentRemoved, int index, bool animate)
{
    removeChildComponent (contentRemoved);

    if (shouldContentComponentBeDeleted(contentRemoved))
    {
        DBG ("deleting component " << contentRemoved->getName());
        delete contentRemoved;
    }
}


void StackComponent::handleStackFocusChange (Component* newFocusContent, int newIndex, int oldIndex, bool animate)
{
    refreshLayout ();
}



StackComponent::Controller::Controller ()
{

}

StackComponent::Controller::~Controller ()
{
    if (targetStack != 0)
        targetStack->removeListener (this);
    targetStack = 0;
}

void StackComponent::Controller::setTargetStack (StackComponent* newTarget)
{
    if (targetStack != newTarget)
    {
        if (targetStack != 0)
            targetStack->removeListener (this);

        targetStack = newTarget;

        if (targetStack != 0)
        {
            targetStack->addListener (this);

            stackComponentContentChanged (targetStack);
            stackComponentFocusChanged (targetStack);
        }
    }
}

StackComponent* StackComponent::Controller::getTargetStack () const
{
    return targetStack;
}

void StackComponent::Controller::refreshFocus ()
{
    if (targetStack != 0)
        stackComponentFocusChanged (targetStack);
}

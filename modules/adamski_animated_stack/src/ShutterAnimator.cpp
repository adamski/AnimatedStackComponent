/*
  ==============================================================================

    ShutterAnimator.cpp
    Created: 4 May 2015 10:40:25pm
    Author:  Adam Elemental

  ==============================================================================
*/

ShutterAnimator::ShutterAnimator (Rectangle<int> focusArea)
    :   StackAnimator(),
        focusArea (focusArea),
        slideDuration (150),
        startSpeed (1.0),
        endSpeed (1.0)
{
    Desktop::getInstance().getAnimator().addChangeListener (this);
}

ShutterAnimator::ShutterAnimator (Rectangle<int> focusArea, int slideDuration, float startSpeed, float endSpeed)
    :   StackAnimator(),
        focusArea (focusArea),
        slideDuration (slideDuration),
        startSpeed (startSpeed),
        endSpeed (endSpeed)
{
    Desktop::getInstance().getAnimator().addChangeListener (this);
}

ShutterAnimator::ShutterAnimator () 
    :   StackAnimator(),
        slideDuration (150),
        startSpeed (1.0),
        endSpeed (1.0)
{
    Desktop::getInstance().getAnimator().addChangeListener (this);
}

ShutterAnimator::ShutterAnimator (int slideDuration, float startSpeed, float endSpeed)
    :   StackAnimator(),
        slideDuration (slideDuration),
        startSpeed (startSpeed),
        endSpeed (endSpeed)
{
    Desktop::getInstance().getAnimator().addChangeListener (this);
}


void ShutterAnimator::setFocusArea (Rectangle<int> newFocusArea)
{
    focusArea = newFocusArea;
}


void ShutterAnimator::refreshLayout ()
{
    for (int i = 0; i < stackComponent->getStackSize (); i++)
    {
        Component* panel = stackComponent->getContentComponentAtIndex (i);
        if (i == stackComponent->getStackFocusIndex())
        {
            panel->setVisible (true);
            panel->setBounds (0, 0, stackComponent->getWidth(), stackComponent->getHeight());
        }
        else
        {
            panel->setVisible (false);
        }
    }
}

void ShutterAnimator::animateContentComponentAdded (Component *newContent, int index)
{

}

/**
 * save the image of the deleted component and display that
 * so that the animation can play on top of it
 */
void ShutterAnimator::animateContentComponentRemoved (Component* contentRemoved, int index)
{
    Rectangle<int> bounds = getCurrentBounds(); 
    // save deleted content image 
    deletedPanel = new ImageComponent("Deleted Panel Snapshot");
    Image contentRemovedImage = contentRemoved->createComponentSnapshot (contentRemoved->getLocalBounds(), false);

    deletedPanel->setImage (contentRemovedImage);

    stackComponent->addAndMakeVisible (deletedPanel);
    deletedPanel->setBounds (bounds);

    // put deletedPanel behind animations
    deletedPanel->toBack();

    if (previousPanel.getComponent() != nullptr)
    {
        previousPanel->setVisible (false);
    }
}


void ShutterAnimator::animateStackFocusChange (Component* newFocusContent, int newIndex, int oldIndex)
{
    jassert (stackComponent != nullptr);
    Component* panel;

    Rectangle<int> bounds = getCurrentBounds();
    isOpening = newIndex > oldIndex;

    // Split the old panel in two (one above, one below the focusArea)
    // Take a snapshot of each 
    // Put the resulting Images into an ImageComponent
    // Animate the ImageComponents to move up and down
    panel = stackComponent->getContentComponentAtIndex (isOpening ? oldIndex : newIndex);
    if (panel != 0)
    {
        // TODO: Tidy this code up - work out whats going with the focusArea adjustments 

        Rectangle<int> topBounds (0, 0, bounds.getWidth(), focusArea.getY()+focusArea.getHeight());
        topSnapshot = new ImageComponent("Top Snapshot");
        topSnapshot->setImage (panel->createComponentSnapshot (topBounds));

        int bottomY = focusArea.getY()+(focusArea.getHeight()*2); 
        Rectangle<int> bottomBounds (0, bottomY, bounds.getWidth(), bounds.getHeight() );
        bottomSnapshot = new ImageComponent("Bottom Snapshot");
        bottomSnapshot->setImage (panel->createComponentSnapshot (bottomBounds));

        focusSnapshot = new ImageComponent("Focus Snapshot");
        DBG (focusArea.toString());
        Rectangle<int> actualFocusArea (0, focusArea.getY()+focusArea.getHeight(), bounds.getWidth(), focusArea.getHeight());
        focusSnapshot->setImage (panel->createComponentSnapshot (actualFocusArea));

        stackComponent->addAndMakeVisible (topSnapshot);
        if (! isOpening) topBounds.setY (0-topBounds.getHeight());
        topSnapshot->setBounds (topBounds);

        stackComponent->addAndMakeVisible (bottomSnapshot);
        bottomBounds.setTop (focusArea.getHeight());
        if (! isOpening) bottomBounds.setY (bottomBounds.getHeight());
        bottomSnapshot->setBounds (bottomBounds);

        stackComponent->addChildComponent (focusSnapshot);
        focusSnapshot->setBounds (actualFocusArea);
        if (isOpening)
        {
            focusSnapshot->setVisible (true);
            Desktop::getInstance().getAnimator().fadeOut (focusSnapshot, slideDuration);
        }
        else
        {
            Desktop::getInstance().getAnimator().fadeIn (focusSnapshot, slideDuration);
        }

        if (isOpening) topBounds.setY (0-topBounds.getHeight());
        else topBounds.setY (0);
        Desktop::getInstance().getAnimator().animateComponent(topSnapshot, topBounds, 1.0f, slideDuration, true, startSpeed, endSpeed);

        if (isOpening) bottomBounds.setY (bottomBounds.getHeight());
        else bottomBounds.setY (focusArea.getY()-focusArea.getHeight());
        Desktop::getInstance().getAnimator().animateComponent(bottomSnapshot, bottomBounds, 1.0f, slideDuration, true, startSpeed, endSpeed);
    }

    if (isOpening)
    {
        panel = stackComponent->getContentComponentAtIndex (newIndex);
        if (panel != 0)
        {
            panel->setVisible (true);
            panel->setBounds (bounds);
            previousPanel = nullptr;
        }
    }
    else
    {
        previousPanel = stackComponent->getContentComponentAtIndex (newIndex);

        if (previousPanel.getComponent() != nullptr)
        {
            previousPanel->setVisible (false);
        }

        panel = stackComponent->getContentComponentAtIndex (oldIndex);
        if (panel != nullptr)
        {
            panel->setVisible (true); 
        }
    }
}


void ShutterAnimator::setDuration (int durationMs, double newStartSpeed, double newEndSpeed)
{
    slideDuration = durationMs;
    startSpeed = newStartSpeed;
    endSpeed = newEndSpeed;
}


/**
 * Check if we've finished an animation and remove the proxy image components 
 * plus other stuff to make it work both for back button and breadcrumb navigation
 */
void ShutterAnimator::changeListenerCallback (ChangeBroadcaster *source) 
{
    if (( ! Desktop::getInstance().getAnimator().isAnimating (topSnapshot) && topSnapshot->getY() == 0 && ! isOpening )
    || (! Desktop::getInstance().getAnimator().isAnimating (bottomSnapshot) && bottomSnapshot->getY() == stackComponent->getHeight() && isOpening ))
    {
        finishedAnimating = true;
    }

    if (previousPanel.getComponent() != nullptr && finishedAnimating)
    {
        if (deletedPanel != nullptr)
        {
            deletedPanel->setVisible (false);
            deletedPanel = nullptr;
        }
        if (previousPanel != nullptr && !previousPanel->isShowing())
        {
            previousPanel->setVisible (true);
            int currentIndex = stackComponent->indexOfContentComponent(previousPanel.getComponent());
            //DBG ("Index: " << currentIndex << ", size: " << stackComponent->getStackSize());

            if (currentIndex < stackComponent->getStackSize()-1)
            {
                // hide next component if were going backwards and not deleted the last component 
                stackComponent->getContentComponentAtIndex (currentIndex + 1)->setVisible (false);
            }
        }
        topSnapshot->setVisible (false);
        bottomSnapshot->setVisible (false);
        focusSnapshot->setVisible (false);
        previousPanel = nullptr;

        //DBG ("removed snapshots");
        finishedAnimating = false;
    }
}

/** 
 * Get current bounds for the StackComponent
 */
Rectangle<int> ShutterAnimator::getCurrentBounds() const
{
    int w = stackComponent->getWidth();
    int h = stackComponent->getHeight();
    return Rectangle<int> (0, 0, w, h);
}




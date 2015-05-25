/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"



//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 400);
    ValueTree data (AnimatedListBoxIds::data);  
    
    ValueTree node1 (AnimatedListBoxIds::node);
    node1.setProperty (AnimatedListBoxIds::title, "Slide", nullptr);
    node1.setProperty (AnimatedListBoxIds::description, "Sliding Animator", nullptr);
    data.addChild (node1, -1, nullptr);

    ValueTree node2 (AnimatedListBoxIds::node);
    node2.setProperty (AnimatedListBoxIds::title, "Shutter", nullptr);
    node2.setProperty (AnimatedListBoxIds::description, "Shutter Animator", nullptr);
    data.addChild (node2, -1, nullptr);

    ValueTree node3 (AnimatedListBoxIds::node);
    node3.setProperty (AnimatedListBoxIds::title, "Fade", nullptr);
    node3.setProperty (AnimatedListBoxIds::description, "Fade Animator", nullptr);
    data.addChild (node3, -1, nullptr);

    addAndMakeVisible (animatedStackComponent = new AnimatedStackComponent());
    animatedStackComponent->setBounds (getBounds());
    
    editorComponent = new EditorComponent();
    shutterAnimator = new ShutterAnimator(300, 0.5, 1.0);

    shutterAnimator->setStackComponent (animatedStackComponent);
    AnimatedStackHelpers::setStackAnimatorForComponent (shutterAnimator, editorComponent);

    animatedStackComponent->push (listBox = new AnimatedListBox (data,
        // itemClicked callback function
        [this] (int row, ListBox* source, ValueTree node, const MouseEvent &e)
        {
            Rectangle<int> rowPosition = source->getRowPosition(row, false);
            DBG (rowPosition.toString());
            DBG (node.toXmlString());
            DBG ("row number clicked: " << row);
            shutterAnimator->setFocusArea (rowPosition);
            animatedStackComponent->push (editorComponent, false);
        }
    ), true);
    listBox->setBounds (getBounds());
    
    //animatedStackComponent->push (homeComponent = new HomeComponent(), true, true, false);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

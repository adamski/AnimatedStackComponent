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

    shutterAnimator = new ShutterAnimator(300, 0.5, 1.0);
    //slideAnimator = new SlideAnimator(300, 0.5, 1.0);

    ValueTree data (Ids::data);  

    ValueTree node1 (Ids::node);
    node1.setProperty (Ids::title, "Item 1", nullptr);
    node1.setProperty (Ids::description, "Blah blah", nullptr);
    data.addChild (node1, -1, nullptr);

    ValueTree node2 (Ids::node);
    node2.setProperty (Ids::title, "Item 2", nullptr);
    node2.setProperty (Ids::description, "Shutter Animator", nullptr);
    data.addChild (node2, -1, nullptr);

    ValueTree node3 (Ids::node);
    node3.setProperty (Ids::title, "Item 3", nullptr);
    node3.setProperty (Ids::description, "Fade Animator", nullptr);
    data.addChild (node3, -1, nullptr);

    homeComponent = new HomeComponent();
    editorComponent = new EditorComponent();

    addAndMakeVisible (header = new StackHeaderComponent());
    addAndMakeVisible (animatedStack = new AnimatedStackComponent());
    
    shutterAnimator->setStackComponent (animatedStack);
    //slideAnimator->setStackComponent (animatedStack);

    AnimatedStackHelpers::setStackAnimatorForComponent(shutterAnimator, editorComponent);

    animatedStack->setComponentID("Stack");

    header->setComponentID("Header");
    header->setTargetStack (animatedStack);
    header->setInterceptsMouseClicks (false,true);

    header->setBounds ("0,0,parent.width,40");
    animatedStack->setBounds ("Header.left,Header.bottom,parent.width,parent.height");

    //setColour (ListBox::backgroundColourId, Colours::black);

    animatedStack->push (homeComponent, true);
    animatedStack->push (listBox = new AnimatedListBox (data,
        // itemClicked callback function
        [this] (int row, ListBox* source, ValueTree node, const MouseEvent &e)
        {
            Rectangle<int> rowPosition = source->getRowPosition(row, false);
            DBG (rowPosition.toString());
            DBG (node.toXmlString());
            DBG ("row number clicked: " << row);
            animatedStack->push (editorComponent, false);
        }
    ), true);
    listBox->setBounds (animatedStack->getBounds());
}

MainContentComponent::~MainContentComponent()
{
    listBox = nullptr;
    homeComponent = nullptr;
    editorComponent = nullptr;
    animatedStack = nullptr;
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
}

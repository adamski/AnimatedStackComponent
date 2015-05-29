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

    editorComponent = new EditorComponent();

    addAndMakeVisible (header = new StackHeaderComponent());
    addAndMakeVisible (animatedStack = new AnimatedStackComponent());
    shutterAnimator = new ShutterAnimator(300, 0.5, 1.0);

    shutterAnimator->setStackComponent (animatedStack);
    AnimatedStackHelpers::setStackAnimatorForComponent (shutterAnimator, editorComponent);

    animatedStack->setComponentID("Stack");

    header->setComponentID("Header");
    header->setTargetStack (animatedStack);
    header->setInterceptsMouseClicks (false,true);

    header->setBounds ("0,0,parent.width,40");
    animatedStack->setBounds ("Header.left,Header.bottom,parent.width,parent.height");

    listBox = new AnimatedListBox (data,
        // itemClicked callback function
        [this] (int row, ListBox* source, ValueTree node, const MouseEvent &e)
        {
            Rectangle<int> rowPosition = source->getRowPosition(row, false);
            DBG (rowPosition.toString());
            DBG (node.toXmlString());
            DBG ("row number clicked: " << row);
            shutterAnimator->setFocusArea (rowPosition);
            editorComponent->setNode (node);
            animatedStack->push (editorComponent, false);
        }
    );

    listBox->setBounds ("Stack.left,Stack.top,parent.width,parent.height");

    animatedStack->push (homeComponent = new HomeComponent(
        [this] ()
        {
            animatedStack->push (listBox, false);
        }), true);
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

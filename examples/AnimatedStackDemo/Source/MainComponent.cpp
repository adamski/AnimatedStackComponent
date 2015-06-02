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
    setColour (ListBox::backgroundColourId, Colours::transparentWhite);
    ValueTree data (AnimatedListBoxIds::data);  

    ValueTree node1 (AnimatedListBoxIds::node);
    node1.setProperty (AnimatedListBoxIds::title, "Item 1", nullptr);
    node1.setProperty (AnimatedListBoxIds::description, "Aliquam mollis ultrices eros, non pretium lectus consectetur placerat. Fusce sollicitudin, orci nec volutpat mattis, ipsum elit vestibulum turpis, ac feugiat dolor sapien et nibh. Vestibulum faucibus, sapien id vehicula vehicula, elit urna rhoncus nisl, eget congue turpis est id sem.", nullptr);
    data.addChild (node1, -1, nullptr);

    ValueTree node2 (AnimatedListBoxIds::node);
    node2.setProperty (AnimatedListBoxIds::title, "Item 2", nullptr);
    node2.setProperty (AnimatedListBoxIds::description, "Donec placerat sollicitudin orci, at auctor arcu luctus vitae. Sed ut nibh viverra, elementum odio dictum, egestas velit.", nullptr);
    data.addChild (node2, -1, nullptr);

    ValueTree node3 (AnimatedListBoxIds::node);
    node3.setProperty (AnimatedListBoxIds::title, "Item 3", nullptr);
    node3.setProperty (AnimatedListBoxIds::description, "Curabitur scelerisque euismod mauris, nec aliquet elit finibus viverra. Morbi vel facilisis nunc. Morbi elit nisi, gravida eget interdum sed, vestibulum vel sapien.", nullptr);
    data.addChild (node3, -1, nullptr);

    ValueTree node4 (AnimatedListBoxIds::node);
    node4.setProperty (AnimatedListBoxIds::title, "Item 4", nullptr);
    node4.setProperty (AnimatedListBoxIds::description, "Integer vitae ultrices dolor, sit amet iaculis sapien. ", nullptr);
    data.addChild (node4, -1, nullptr);

    ValueTree node5 (AnimatedListBoxIds::node);
    node5.setProperty (AnimatedListBoxIds::title, "Item 5", nullptr);
    node5.setProperty (AnimatedListBoxIds::description, "Aenean molestie leo a vulputate tincidunt. Sed semper urna vitae urna aliquet vehicula.", nullptr);
    data.addChild (node5, -1, nullptr);

    editorComponent = new EditorComponent();

    addAndMakeVisible (header = new StackHeaderComponent());
    addAndMakeVisible (animatedStack = new AnimatedStackComponent());

    stackAnimators.add (new ShutterAnimator(600, 0.5, 1.0));
    stackAnimators.add (new SlideAnimator(600, 0.5, 1.0));
    stackAnimators.add (new DefaultStackAnimator());

    for (auto animator : stackAnimators)
    {
        animator->setStackComponent (animatedStack);
    }

    AnimatedStackHelpers::setStackAnimatorForComponent (stackAnimators.getFirst(), editorComponent);

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
            Rectangle<int> rowPosition = source->getRowPosition(row, true);
            StackAnimator::Ptr stackAnimator = AnimatedStackHelpers::getStackAnimatorForComponent (editorComponent);
            stackAnimator->setFocusArea (rowPosition);
            editorComponent->setNode (node);
            animatedStack->push (editorComponent, false);
        }
    );

    listBox->setBounds ("Stack.left,Stack.top,parent.width,parent.height");

    animatedStack->push (homeComponent = new HomeComponent(
        [this] ()
        {
            animatedStack->push (listBox, false);
        },
        [this] (int selectedIndex)
        {
            AnimatedStackHelpers::setStackAnimatorForComponent (stackAnimators [selectedIndex], editorComponent);
        }
        ), true);
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

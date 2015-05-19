/*
  ==============================================================================

    ValueTreeStackPanel.cpp
    Created: 13 Mar 2011 10:53:12am
    Author:  Haydxn

  ==============================================================================
*/

#include "ValueTreeStackPanel.h"
#include "ValueTreeListBox.h"

class ValueTreeListProp	:	public PropertyComponent
{
public:

	ValueTreeListProp (const ValueTree& node, ValueTreeListBox::Listener* listener, int height = 150)
		:	PropertyComponent ("Children",height)
	{
		addAndMakeVisible (&list);
		list.setContextNode (node);
		list.addListener (listener);
	}

	~ValueTreeListProp ()
	{
	}

	void refresh ()
	{
	}

private:
	
	ValueTreeListBox list;

};


ValueTreeStackPanel::ValueTreeStackPanel (const ValueTree& nodeToUse)
:	node (nodeToUse)
{
	setOpaque (true);
	addAndMakeVisible (&properties);
	properties.setComponentID("Props");
	properties.setBounds("0,0,parent.width,parent.height");
	repopulateProperties ();
	properties.setBufferedToImage (true);
	setBufferedToImage (true);

	StackHeaderComponent::setStackContentTitle (this, node.getType().toString());
	StackNavigationList::setContentTitle (this, node.getType().toString());
}

ValueTreeStackPanel::~ValueTreeStackPanel ()
{
}

void ValueTreeStackPanel::paint (Graphics& g)
{
	g.fillAll (Colours::grey);
}

AnimatedStackComponent* ValueTreeStackPanel::getStack ()
{
	return static_cast<AnimatedStackComponent*> (StackComponent::findForContent (this));
}

void ValueTreeStackPanel::pushAfter (Component* newComponent, bool autoFocus, bool animate)
{
	StackComponent* stack = getStack();
	if (stack != 0)
	{
		stack->pushAfterExisting (this, newComponent, true, autoFocus, animate);
	}
}

void ValueTreeStackPanel::pop ()
{
	StackComponent* stack = getStack();
	if (stack != 0)
	{
		int index = stack->indexOfContentComponent (this);
		stack->popComponentsAboveIndex (index-1);
	}
}

void ValueTreeStackPanel::valueTreeListBoxItemDoubleClicked (ValueTreeListBox* source, const MouseEvent& e, int index, const ValueTree& itemNode)
{
    ValueTreeStackPanel* nextPanel = new ValueTreeStackPanel (itemNode);
    if (index == 1)
    {
        Rectangle<int> rowPosition = source->getListBox().getRowPosition(index, false);
        ShutterAnimator::Ptr shutterAnimator = new ShutterAnimator(rowPosition, 300, 0.5, 1.0);
        shutterAnimator->setStackComponent(getStack());
        AnimatedStackHelpers::setStackAnimatorForComponent(shutterAnimator, nextPanel);
    }
    pushAfter (nextPanel,true,true);
}

void ValueTreeStackPanel::valueTreeListBoxItemClicked (ValueTreeListBox* source, const MouseEvent& e, int index, const ValueTree& itemNode)
{
}

void ValueTreeStackPanel::valueTreeListBoxContextNodeAssigned (ValueTreeListBox* source, const ValueTree& newContextNode)
{
}

void ValueTreeStackPanel::repopulateProperties ()
{
	properties.clear ();
	Array<PropertyComponent*> props;

	props.add (new ValueTreeListProp (node,this));
	properties.addSection ("Children", props, true);
	props.clear();

	int n = node.getNumProperties ();
	for (int i=0; i<n; i++)
	{
		Identifier name(node.getPropertyName (i));
		Value value = node.getPropertyAsValue (name,0);
		PropertyComponent* c = new TextPropertyComponent (value,name.toString(),255,false);
		props.add (c);
	}
	properties.addSection ("Properties", props, true);

}

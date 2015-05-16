/*
  ==============================================================================

    ValueTreeListBox.cpp
    Created: 13 Mar 2011 11:39:27am
    Author:  Haydxn

  ==============================================================================
*/

#include "ValueTreeListBox.h"

/////////////////////////////////////////////////////////////////

ValueTreeListBox::ItemComponent::ItemComponent (ValueTreeListBox* parent)
:	owner (parent)
{
	setInterceptsMouseClicks (false,false);
}

ValueTree ValueTreeListBox::ItemComponent::getNode ()
{
	return node;
}

void ValueTreeListBox::ItemComponent::setNode (const ValueTree& newNode)
{
	if (newNode != node)
	{
		node = newNode;
		nodeAssigned (node);
	}
}

void ValueTreeListBox::ItemComponent::nodeAssigned (const ValueTree& node)
{
}

void ValueTreeListBox::ItemComponent::paint (Graphics& g)
{
	if (isSelected())
	{
		g.fillAll ( Colours::hotpink.withAlpha(0.5f));
	}

	String text (getNode().getType().toString());
	g.drawFittedText (text,0,0,getWidth(),getHeight(),Justification::centred,3);
}

bool ValueTreeListBox::ItemComponent::isSelected ()
{
	return selected;
}

void ValueTreeListBox::ItemComponent::setSelected (bool shouldBeSelected)
{
	if (selected != shouldBeSelected)
	{
		selected = shouldBeSelected;
		selectednessChanged ();
	}
}

void ValueTreeListBox::ItemComponent::selectednessChanged ()
{
	repaint ();
}

ValueTreeListBox* ValueTreeListBox::ItemComponent::getOwner () const
{
	return owner;
}

/////////////////////////////////////////////////////////////////

ValueTreeListBox::ValueTreeListBox ()
{
	addAndMakeVisible (&listBox);
	listBox.setBounds (RelativeRectangle("0,0,parent.width,parent.height"));
	listBox.setModel (this);
	setOpaque(true);
}

ValueTreeListBox::~ValueTreeListBox ()
{
	contextNode.removeListener(this);
}


void ValueTreeListBox::Listener::valueTreeListBoxContextNodeAssigned (ValueTreeListBox* source, const ValueTree& newContextNode)
{

}

void ValueTreeListBox::addListener (Listener* listener)
{
	listeners.add (listener);
}

void ValueTreeListBox::removeListener (Listener* listener)
{
	listeners.remove (listener);
}

/////////////////////////////////////////////////////////////////

void ValueTreeListBox::resized ()
{
}

/////////////////////////////////////////////////////////////////

int ValueTreeListBox::getNumRows ()
{
	return contextNode.getNumChildren ();
}

ValueTree ValueTreeListBox::getValueTreeForRow (int rowIndex)
{
	return contextNode.getChild (rowIndex);
}

ValueTreeListBox::ItemComponent* ValueTreeListBox::createItemComponent ()
{
	return new ItemComponent (this);
}

/////////////////////////////////////////////////////////////////

void ValueTreeListBox::refresh ()
{
	listBox.updateContent ();
}

/////////////////////////////////////////////////////////////////

void ValueTreeListBox::setContextNode (const ValueTree& newNode)
{
	if (contextNode != newNode)
	{
		contextNode.removeListener (this);

		contextNode = newNode;
		contextNodeAssigned (newNode);

		listeners.call (&Listener::valueTreeListBoxContextNodeAssigned, this, getContextNode());

		refresh ();
		contextNode.addListener (this);
	}
}

ValueTree ValueTreeListBox::getContextNode ()
{
	return contextNode;
}

void ValueTreeListBox::contextNodeAssigned (const ValueTree& newNode)
{
	refresh ();
}

/////////////////////////////////////////////////////////////////

// Implementing ValueTree::Listener
void ValueTreeListBox::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& prop)
{
}

void ValueTreeListBox::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
}

void ValueTreeListBox::valueTreeChildRemoved (ValueTree& parentTree,
                            ValueTree& childWhichHasBeenRemoved,
                            int indexFromWhichChildWasRemoved)
{
}

void ValueTreeListBox::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
}

void ValueTreeListBox::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged)
{
}

// Implementing ListBoxModel
void ValueTreeListBox::paintListBoxItem (int rowNumber, Graphics& g, int w, int h, bool selected)
{
	g.setColour(Colours::black.withAlpha(0.4f));
	g.drawHorizontalLine (h-1,0.0f,(float)w);
}

void ValueTreeListBox::changeItemNode (int row, Component* comp, const ValueTree& newNode)
{
	ItemComponent* item = dynamic_cast<ItemComponent*> (comp);

	item->setNode (newNode);

	itemNodeChanged (row, item, newNode);
}

Component* ValueTreeListBox::refreshComponentForRow (int rowNumber, bool selected, Component* existing)
{
	if (rowNumber >= getNumRows())
	{
		// We're just going to destroy excess items
		if (existing)
		{
			delete existing;
		}
		return 0;
	}

	ValueTree node = getValueTreeForRow (rowNumber);

	ItemComponent* comp = dynamic_cast<ItemComponent*> (existing);
	if (comp == NULL)
	{	
		comp = new ItemComponent (this);
		changeItemNode (rowNumber, comp, node);
	}
	else
	{
		if (comp->getNode() != node)
		{
			changeItemNode (rowNumber, comp, node);
		}
		else
		{
			// maybe some light 'refresh' call?
		}
	}

	if (comp)
	{
		comp->setSelected (selected);
	}
	return comp;
}

void ValueTreeListBox::listBoxItemClicked (int row, const MouseEvent &e)
{
	listeners.call (&Listener::valueTreeListBoxItemClicked, this, e, row, getValueTreeForRow (row));
}

void ValueTreeListBox::listBoxItemDoubleClicked (int row, const MouseEvent &e)
{
	listeners.call (&Listener::valueTreeListBoxItemDoubleClicked, this, e, row, getValueTreeForRow (row));
}

ListBox& ValueTreeListBox::getListBox ()
{
	return listBox;
}

void ValueTreeListBox::itemNodeChanged (int row, ItemComponent* comp, const ValueTree& newNode)
{
}


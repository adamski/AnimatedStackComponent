/*
  ==============================================================================

    StackNavigationList.cpp
    Created: 13 Mar 2011 12:37:14pm
    Author:  Haydxn

  ==============================================================================
*/

#include "StackNavigationList.h"

using namespace juce;

const Identifier StackNavigationList::titlePropertyId ("StackNavigationList_Title");

StackNavigationList::StackNavigationList ()
{
	listbox.setModel (this);
	addAndMakeVisible(&listbox);
	listbox.setBounds ("5,5,parent.width-5,parent.height-5");
	listbox.setRowHeight(40);
	listbox.setColour (ListBox::backgroundColourId, Colours::transparentBlack);
}

StackNavigationList::~StackNavigationList ()
{
}

int StackNavigationList::getNumRows ()
{
	StackComponent* stack = getTargetStack ();
	if (stack != 0)
		return stack->getStackSize ();

	return 0;
}

void StackNavigationList::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.setColour (Colours::hotpink);
		g.fillRect (2,2,width-4,height-4);
	}

	StackComponent* stack = getTargetStack ();
	if (stack != 0)
	{
		g.setColour (Colours::black);

		Component* c = stack->getContentComponentAtIndex (rowNumber);
		String text = getContentTitle (c);

		g.drawFittedText (text,0,0,width,height,Justification::centred,1);
	}

	float yoffset = height * 0.2f;
	float x = (float) width/2;

	float headLength = 7.0f;
	float headWidth = 7.0f;
	float lineThickness = 2.0f;

	if (rowNumber > 0)
	{
		Line<float> topline (x, -yoffset, x, yoffset);
		g.drawArrow (topline, lineThickness, headWidth, headLength);
	}

	if (rowNumber < getNumRows()-1)
	{
		Line<float> botline (x, height-yoffset, x, height+yoffset);
		g.drawArrow (botline, lineThickness, headWidth, headLength);
	}
}

void StackNavigationList::selectedRowsChanged (int lastRowSelected)
{
	StackComponent* stack = getTargetStack ();
	if (stack != 0)
	{
		if (lastRowSelected != stack->getStackFocusIndex() && lastRowSelected != -1)
			stack->setStackFocusIndex (lastRowSelected, true);
	}
}

void StackNavigationList::stackComponentContentChanged (StackComponent* stack)
{
	listbox.updateContent ();
	refreshFocus ();
	repaint ();
}

void StackNavigationList::stackComponentFocusChanged (StackComponent* stack)
{
	int row = stack->getStackFocusIndex ();
	if (row != listbox.getSelectedRow())
	{
		listbox.selectRow (row);
	}
}

void StackNavigationList::setContentTitle (Component* content, const String& title)
{
	if (content != 0)
		content->getProperties ().set (titlePropertyId, title);
}

String StackNavigationList::getContentTitle (Component* content)
{
	if (content != 0)
		return content->getProperties() [titlePropertyId];
	return String::empty;
}

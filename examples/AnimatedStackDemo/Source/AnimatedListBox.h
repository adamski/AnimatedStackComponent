/*
  ==============================================================================

    AnimatedListBox.h
    Created: 13 Apr 2015 11:26:11pm
    Author:  Adam Elemental

  ==============================================================================
*/

#ifndef ANIMATEDLISTBOX_H_INCLUDED
#define ANIMATEDLISTBOX_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <functional>

//==============================================================================

namespace AnimatedListBoxIds 
{
    static const Identifier data ("Data");
    static const Identifier node ("Node");
    static const Identifier title ("Title");
    static const Identifier description ("Description");
}

class AnimatedListBox    : public ListBox, public ListBoxModel 
{
public:
    typedef std::function <void(int, ListBox*, ValueTree, const MouseEvent&)> ItemCallbackFunction;

    AnimatedListBox(ValueTree data,  ItemCallbackFunction itemClicked)
    :   ListBox("Animated ListBox", this), 
        data (data), 
        itemClicked (itemClicked) 
    {
        setModel (this);
        this->setRowHeight (45); // use proportionOfHeight plus min height, e.g. for retina screens
    }

    int getNumRows() 
    {
        return data.getNumChildren ();
    }

    ValueTree getValueTreeForRow (int rowIndex)
    {
        return data.getChild (rowIndex);
    }
    
    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
    {
        return nullptr;
    }

    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) 
    {
        g.fillAll (Colour (0xff001F36));
        
        g.setFont (Font (16.0f));
        g.setColour (Colours::whitesmoke);

        if (rowIsSelected)
        {
            g.setColour (Colours::whitesmoke);
        }
        else
        {
            g.setColour (Colours::olive);
        }
        g.drawRect (0, 0, getWidth(), getRowHeight());

        String title = getValueTreeForRow (rowNumber).getProperty (AnimatedListBoxIds::title);
        g.drawText(title, 0, 0, width, height, Justification::centred, true);
    
    }

    void paint (Graphics& g)
    {
        g.fillAll (Colours::transparentBlack);
    }

    void listBoxItemClicked (int row, const MouseEvent &e)
    {
        DBG (data.getChild(row).toXmlString());
        if (itemClicked != nullptr) 
        {
            itemClicked (row, this, getValueTreeForRow(row), e);
        }
    }

private:
    ValueTree data;
    ItemCallbackFunction itemClicked;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnimatedListBox)
};


#endif  // ANIMATEDLISTBOX_H_INCLUDED

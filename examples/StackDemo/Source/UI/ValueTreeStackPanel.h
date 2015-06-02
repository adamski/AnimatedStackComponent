/*
  ==============================================================================

    ValueTreeStackPanel.h
    Created: 13 Mar 2011 10:53:12am
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __VALUETREESTACKPANEL_H_3FD24CC7__
#define __VALUETREESTACKPANEL_H_3FD24CC7__

#include "ValueTreeListBox.h"

class ValueTreeStackPanel	:	public Component, public ValueTreeListBox::Listener
{
    public:

        ValueTreeStackPanel (const ValueTree& nodeToUse);
        ~ValueTreeStackPanel ();

        StackComponent* getStack ();

        void paint (Graphics& g);

        void pushAfter (Component* newComponent, bool autoFocus, bool animate);
        void pop ();

        void valueTreeListBoxItemDoubleClicked (ValueTreeListBox* source, const MouseEvent& e, int index, const ValueTree& itemNode);
        void valueTreeListBoxItemClicked (ValueTreeListBox* source, const MouseEvent& e, int index, const ValueTree& itemNode);
        void valueTreeListBoxContextNodeAssigned (ValueTreeListBox* source, const ValueTree& newContextNode);

        void repopulateProperties ();

    private:

        PropertyPanel		properties;
        ValueTree			node;

};



#endif  // __VALUETREESTACKPANEL_H_3FD24CC7__

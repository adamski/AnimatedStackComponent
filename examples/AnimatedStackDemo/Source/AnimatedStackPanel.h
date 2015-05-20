/*
  ==============================================================================

    AnimatedStackPanel.h
    Created: 13 Mar 2011 10:53:12am
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __VALUETREESTACKPANEL_H_3FD24CC7__
#define __VALUETREESTACKPANEL_H_3FD24CC7__

#include "AnimatedListBox.h"

class AnimatedStackPanel : public Component
{
    public:

        AnimatedStackPanel (const ValueTree& data);
        ~AnimatedStackPanel ();

        AnimatedStackComponent* getStack ();

        void paint (Graphics& g);

        void pushAfter (Component* newComponent, bool autoFocus, bool animate);
        void pop ();

        //void valueTreeListBoxContextNodeAssigned (ValueTreeListBox* source, const ValueTree& newContextNode);

    private:

        ValueTree data;

};



#endif  // __VALUETREESTACKPANEL_H_3FD24CC7__

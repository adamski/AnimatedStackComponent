/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_C41A107FFA390B74__
#define __JUCE_HEADER_C41A107FFA390B74__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class EditorComponent  : public Component,
                         public LabelListener
{
public:
    //==============================================================================
    EditorComponent ();
    ~EditorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setNode (ValueTree& newNode);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void labelTextChanged (Label* labelThatHasChanged);
    void focusLost (FocusChangeType cause);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ValueTree node;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> textEditor;
    ScopedPointer<Label> titleLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_C41A107FFA390B74__

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

#ifndef __JUCE_HEADER_BDEAC9DB91241E30__
#define __JUCE_HEADER_BDEAC9DB91241E30__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include <functional>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class HomeComponent  : public Component,
                       public ButtonListener,
                       public ComboBoxListener
{
public:
    //==============================================================================
    HomeComponent (std::function <void()> listButtonCallback, std::function <void(int)> comboBoxCallback);
    ~HomeComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    typedef std::function <void()> ListButtonCallbackFunction;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::function <void()> listButtonCallback;
    std::function <void(int)> comboBoxCallback;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> listButton;
    ScopedPointer<ComboBox> comboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomeComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_BDEAC9DB91241E30__

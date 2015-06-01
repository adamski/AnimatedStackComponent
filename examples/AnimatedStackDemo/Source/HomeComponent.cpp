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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "HomeComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
HomeComponent::HomeComponent (std::function <void()> listButtonCallback, std::function <void(int)> comboBoxCallback)
    : listButtonCallback (listButtonCallback), comboBoxCallback (comboBoxCallback)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (listButton = new TextButton ("ListButton"));
    listButton->setButtonText (TRANS("View ListBox"));
    listButton->addListener (this);

    addAndMakeVisible (comboBox = new ComboBox ("new combo box"));
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (TRANS("Please select"));
    comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox->addItem (TRANS("Shutter"), 1);
    comboBox->addItem (TRANS("Slider"), 2);
    comboBox->addItem (TRANS("Default (none)"), 3);
    comboBox->addListener (this);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    comboBox->setSelectedItemIndex (0, NotificationType::dontSendNotification);
    //[/Constructor]
}

HomeComponent::~HomeComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    listButton = nullptr;
    comboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void HomeComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xcd000000));

    g.setColour (Colours::aliceblue);
    g.setFont (Font (32.40f, Font::plain));
    g.drawText (TRANS("Home Screen"),
                proportionOfWidth (0.2538f), proportionOfHeight (0.2044f), proportionOfWidth (0.5076f), proportionOfHeight (0.0667f),
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void HomeComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    listButton->setBounds (proportionOfWidth (0.3046f), proportionOfHeight (0.4089f), proportionOfWidth (0.4010f), proportionOfHeight (0.1067f));
    comboBox->setBounds (proportionOfWidth (0.3046f), proportionOfHeight (0.6044f), proportionOfWidth (0.4061f), proportionOfHeight (0.0533f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void HomeComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == listButton)
    {
        //[UserButtonCode_listButton] -- add your button handler code here..
        listButtonCallback();
        //[/UserButtonCode_listButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void HomeComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox)
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        int selectedIndex = comboBox->getSelectedItemIndex();
        comboBoxCallback (selectedIndex);
        //[/UserComboBoxCode_comboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="HomeComponent" componentName=""
                 parentClasses="public Component" constructorParams="std::function &lt;void()&gt; listButtonCallback, std::function &lt;void(int)&gt; comboBoxCallback"
                 variableInitialisers="listButtonCallback (listButtonCallback), comboBoxCallback (comboBoxCallback)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="cd000000">
    <TEXT pos="25.381% 20.444% 50.761% 6.667%" fill="solid: fff0f8ff" hasStroke="0"
          text="Home Screen" fontname="Default font" fontsize="32.399999999999998579"
          bold="0" italic="0" justification="36"/>
  </BACKGROUND>
  <TEXTBUTTON name="ListButton" id="fad5fb2aa8a4b9d4" memberName="listButton"
              virtualName="" explicitFocusOrder="0" pos="30.457% 40.889% 40.102% 10.667%"
              buttonText="View ListBox" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="281b9558752b5ef3" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="30.457% 60.444% 40.609% 5.333%"
            editable="0" layout="33" items="Shutter&#10;Slider&#10;Default (none)"
            textWhenNonSelected="Please select" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

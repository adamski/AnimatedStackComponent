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
#include "Identifiers.h"
//[/Headers]

#include "EditorComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
EditorComponent::EditorComponent ()
    : node (node)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (textEditor = new TextEditor ("text editor"));
    textEditor->setMultiLine (true);
    textEditor->setReturnKeyStartsNewLine (true);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (false);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (false);
    textEditor->setColour (TextEditor::textColourId, Colours::aliceblue);
    textEditor->setColour (TextEditor::backgroundColourId, Colour (0xcd000000));
    textEditor->setColour (CaretComponent::caretColourId, Colours::aliceblue);
    textEditor->setText (TRANS("[some description]"));

    addAndMakeVisible (titleLabel = new Label ("new label",
                                               TRANS("title")));
    titleLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 19.80f, Font::plain));
    titleLabel->setJustificationType (Justification::centred);
    titleLabel->setEditable (true, true, false);
    titleLabel->setColour (Label::textColourId, Colours::aliceblue);
    titleLabel->setColour (TextEditor::textColourId, Colours::aliceblue);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    titleLabel->addListener (this);


    //[UserPreSize]

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

EditorComponent::~EditorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textEditor = nullptr;
    titleLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EditorComponent::paint (Graphics& g)
{

    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void EditorComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    textEditor->setBounds (proportionOfWidth (0.1016f), proportionOfHeight (0.2135f), proportionOfWidth (0.7922f), proportionOfHeight (0.6934f));
    titleLabel->setBounds (proportionOfWidth (0.2031f), proportionOfHeight (0.0712f), proportionOfWidth (0.5688f), proportionOfHeight (0.0893f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EditorComponent::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == titleLabel)
    {
        //[UserLabelCode_titleLabel] -- add your label text handling code here..
        if (node.isValid()) node.setProperty (Ids::title, titleLabel->getText(), nullptr);
        //[/UserLabelCode_titleLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

// void EditorComponent::focusLost (FocusChangeType cause)
// {
//     //[UserCode_focusLost] -- Add your code here...
//     if (node.isValid()) node.setProperty (Ids::description, textEditor->getText(), nullptr);
//     //[/UserCode_focusLost]
// }



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void EditorComponent::setNode (ValueTree & newNode)
{
    node = newNode;
    textEditor->setText (node.getProperty(Ids::description), NotificationType::dontSendNotification);
    titleLabel->setText (node.getProperty(Ids::title), NotificationType::dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="EditorComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers="node (node)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="focusLost (FocusChangeType cause)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff000000"/>
  <TEXTEDITOR name="text editor" id="e2f8829b3b6d3b78" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="10.152% 21.333% 79.188% 69.333%"
              textcol="fff0f8ff" bkgcol="cd000000" caretcol="fff0f8ff" initialText="[some description]"
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="4953d297d6c4b212" memberName="titleLabel"
         virtualName="" explicitFocusOrder="0" pos="20.305% 7.111% 56.853% 8.889%"
         textCol="fff0f8ff" edTextCol="fff0f8ff" edBkgCol="0" labelText="title"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="19.800000000000000711"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

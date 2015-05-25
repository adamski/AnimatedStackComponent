/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AnimatedListBox.h"
#include "HomeComponent.h"
#include "EditorComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();

private:
    ScopedPointer<AnimatedListBox> listBox;
    ScopedPointer<AnimatedStackComponent> animatedStackComponent;
    ScopedPointer<HomeComponent> homeComponent;
    ScopedPointer<EditorComponent> editorComponent;
    ShutterAnimator::Ptr shutterAnimator;
    //SlideAnimator::Ptr slideAnimator;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
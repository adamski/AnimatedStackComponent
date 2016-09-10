/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               adamski_animated_stack
  vendor:           adamski
  version:          0.1.0
  name:             Animated Stack Component
  description:      Extension of Stack Component allowing different animations to be used per component
  website:          https:/github.com/adamski/AnimatedStack
  license:          The MIT License (MIT)

  dependencies:     juce_core juce_gui_basics juce_graphics juce_events haydxn_stack_component

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/


#ifndef ADAMSKI_ANIMATED_STACK_H_INCLUDED
#define ADAMSKI_ANIMATED_STACK_H_INCLUDED

//=============================================================================
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <haydxn_stack_component/haydxn_stack_component.h>

class AnimatedStackComponent;
class StackAnimator;
class DefaultStackAnimator;

#include "src/AnimatedStackComponent.h"
#include "src/StackAnimator.h"
#include "src/DefaultStackAnimator.h"
#include "src/SlideAnimator.h"
#include "src/ShutterAnimator.h"

#endif   // ADAMSKI_ANIMATED_STACK_H_INCLUDED

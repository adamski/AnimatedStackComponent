/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               haydxn_stack_component
  vendor:           haydxn
  version:          1.0.2
  name:             Stack Component
  description:      Flexible UI container component, similar to a TabbedComponent
  website:          https:/github.com/adamski/AnimatedStack
  license:          The MIT License (MIT)

  dependencies:     juce_core juce_gui_basics juce_graphics juce_events haydxn_stack_component

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/


#ifndef HAYDXN_STACK_COMPONENT_H_INCLUDED
#define HAYDXN_STACK_COMPONENT_H_INCLUDED

//=============================================================================
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

//namespace hx
//{

class StackComponent;
class SlidingStackComponent;
class StackHeaderComponent;
class StackNavigationList;
class HeaderLabel;
class MarginedContainerComponent;

#include "src/StackComponent.h"
#include "src/SlidingStackComponent.h"
#include "src/StackHeaderComponent.h"
#include "src/StackNavigationList.h"
#include "src/HeaderLabel.h"
#include "src/MarginedContainerComponent.h"

//}

#endif   // HAYDXN_STACK_COMPONENT_H_INCLUDED

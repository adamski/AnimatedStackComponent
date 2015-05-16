#if defined (HAYDXN_STACK_COMPONENT_H_INCLUDED) && ! JUCE_AMALGAMATED_INCLUDE
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE cpp file"
#endif

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"

#include "haydxn_stack_component.h"

// namespace hx 
// {
using namespace juce;

#include "src/StackComponent.cpp"
#include "src/SlidingStackComponent.cpp"
#include "src/StackHeaderComponent.cpp"
#include "src/StackNavigationList.cpp"
#include "src/HeaderLabel.cpp"
#include "src/MarginedContainerComponent.cpp"
// }

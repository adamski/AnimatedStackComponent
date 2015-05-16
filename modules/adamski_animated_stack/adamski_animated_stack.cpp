#if defined (ADAMSKI_ANIMATED_STACK_H_INCLUDED) && ! JUCE_AMALGAMATED_INCLUDE
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

#include "adamski_animated_stack.h"

#include "src/AnimatedStackComponent.cpp"
#include "src/StackAnimator.cpp"
#include "src/SlideAnimator.cpp"
#include "src/ShutterAnimator.cpp"


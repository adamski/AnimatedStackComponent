# AnimatedStackComponent
Extension of @haydxn's StackComponent as JUCE modules

Incorporates additional classes to allow a more generalised way of applying animations to a StackComponent.

It basically allows different Components in a Stack to have different animations. 

Animations are defined in classes derived from StackAnimator. 

AnimatedStackComponent inherits from StackComponent. It defines a couple of helper functions to attach and remove StackAnimator instances to Components:

Please have a look at the demos for examples. More detailed documentation to follow. 

--

*Please note:* this work is based on @haydxn's original StackComponent as posted on the JUCE forum in March 2011. I have modified it to work with the latest JUCE version 3.1.1, and I've also modified the original StackDemo to use the AnimatedStackComponent instead of SlidingStackComponent.

I have taken the liberty of packaging the StackComponent classes into a module, and made the module a dependency of AnimatedStackComponent. 



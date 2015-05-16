/*
  ==============================================================================

    StackComponent.h
    Created: 5 Mar 2011 1:20:56pm
    Author:  Haydxn
    Modified: 14 May 2015
    Modifier: Adam Elemental

  ==============================================================================
*/

#ifndef __STACKCOMPONENT_H_695847AD__
#define __STACKCOMPONENT_H_695847AD__

#include "JuceHeader.h"

/**
	This is a special UI container component, similar to a TabbedComponent.

	Components can be pushed on to (and popped from) the stack. The focus
	can be shifted to any component within the stack, or you can just let it
	automatically focus the head of the stack.

	It's been designed to be fully customisable in terms of how the content
	components are actually held and arranged. The default implementation
	simply fills the StackComponent with the currently focused content.
	By subclassing and overriding the virtual functions, it's possible
	to animate and arrange the content components in almost any manner
	desired.

*/

namespace StackComponentHelpers
{

    static const juce::Identifier deletionFlagId ("StackComponent_Delete");

};



class StackComponent	:	public juce::Component
{
public:

	StackComponent ();
	virtual ~StackComponent ();

	/** Pushes a new content component onto the top of the stack. */
	void push (juce::Component* contentComponent, bool shouldBeDeleted, bool autoFocus = true, bool animate = true);
	/** This pops all components that are above the specified existing component
		in the stack, and then pushes the new component above it. */
	void pushAfterExisting (juce::Component* existing, Component* contentComponent, bool shouldBeDeleted, bool autoFocus = true, bool animate = true);

	/** Pops the specified number of components from the top of the stack. */
	void pop (int numberToRemove = 1, bool autoFocus = true, bool animate = true);
	/** Pops all components that are above the specified existing content
		component in the stack. */
	void popComponentsAbove (juce::Component* component, bool autoFocus = true, bool animate = true);
	/** Pops all components that are above the specified position in the stack. */
	void popComponentsAboveIndex (int index, bool autoFocus = true, bool animate = true);

	/** Removes all components from the stack. */
	void clearStack (bool animate);

	/** Returns the index (i.e. position within the stack) of the specified
		content component, or -1 if it is not held in the stack. */
	int indexOfContentComponent (juce::Component* contentToFind) const;
	/** Returns a pointer to the content component at the specified stack
		index. */
	Component* getContentComponentAtIndex (int index) const;
	/** Returns the number of content components held in the stack. */
	int getStackSize () const;

	/** Sets which content component should be focused by its stack
		index. */
	void setStackFocusIndex (int index, bool animate = true);
	/** Sets which content component should be focused by a relative
		stack index (e.g. -1 would focus the component immediately below
		the currently focused content component. */
	void setStackFocusRelative (int relativeIndex, bool animate = true);
	/** Sets the specified content component to be the focus. */
	void setStackFocusContent (juce::Component* contentComponent, bool animate = true);
	/** Sets the focus to the content component at the top of the stack. */
	void setStackFocusToTop (bool animate = true);

	/** Returns the stack index of the currently focused content component. */
	int getStackFocusIndex () const;
	/** Returns a pointer to the currently focused content component. */
	juce::Component* getStackFocusContent () const;

	void resized ();

	/**	
		Listener class for receiving StackComponent notifications.
	*/
	class Listener
	{
	public:

		/** Called whenever the composition of the stack changes.
			(i.e. when a content component is pushed or popped). */
		virtual void stackComponentContentChanged (StackComponent* view) = 0;

		/** Called when the stack changes focus to a different
			content component. */
		virtual void stackComponentFocusChanged (StackComponent* view) = 0;
	};

	/** Registers a listener with this StackComponent. */
	void addListener (Listener* listener);
	/** Unregisters a listener from this StackComponent. */
	void removeListener (Listener* listener);

	/*
		Simple base class for components that are meant to control a StackComponent.
		(e.g. a breadcrumb-trail, navigator strip, etc...). Not a particularly
		complex class, but does handle the boring job of maintaining a connection
		to a target StackComponent. 
	*/
	class Controller	:	public juce::Component,
							public StackComponent::Listener
	{
	public:

		Controller ();
		virtual ~Controller ();

		/** Sets which StackComponent this should cooperate with. This
			automatically handles listener registration, and also ensures
			that the listener callbacks are called automatically when
			assigning the stack. */
		void setTargetStack (StackComponent* target);
		/** Returns a pointer to the target StackComponent. */
		StackComponent* getTargetStack () const;

		/** Helper to trigger the 'focus changed' notification. */
		void refreshFocus ();

		virtual void stackComponentContentChanged(StackComponent* stack) = 0;
		virtual void stackComponentFocusChanged(StackComponent* stack) = 0;

	private:

		juce::Component::SafePointer<StackComponent> targetStack;
	};

	static StackComponent* findForContent (juce::Component* content);

protected:

	enum AutoFocusOrder
	{
		autoFocusBeforeContentChange,
		autoFocusAfterContentChange
	};
	void setPopAutoFocusOrder (AutoFocusOrder order);

	/** Causes a 'content changed' notification to be sent to all listeners. */
	void stackChanged ();
	/** Causes a 'focus changed' notification to be sent to all listeners. */
	void stackFocusChanged ();

	/** This function should ensure that all the content components are suitably
		arranged for the current state of the stack and its focus. */
	virtual void refreshLayout ();

	/** This function is responsible for bringing a new content component into
		whatever display system is being used. For example, the default implementation 
		simply adds the content component as a child of this stack component. 
	*/
	virtual void handleContentComponentAdded (juce::Component* newContent, int index, bool animate);

	/** This function is responsible for taking a given content component out of
		whatever display system is being used. 
		
		It is essential to be aware that this function marks the end of the 
		StackComponent's dealings with a given content component. This is important
		because it means this function is responsible for deleting any components
		which are supposed to be deleted when they are popped.

		This behaviour is required in order to minimise the restrictions placed
		on a subclass' ability to animate the arrangement. If the removal of the 
		component is to happen over time, it naturally cannot be automatically
		deleted after this call has been made (it could be replaced with a proxy
		Component - and that's certainly the recommended approach - but it may not
		always be possible or desired). Once this function has been called, it
		is the subclass' duty to ensure the proper destruction of the content
		if 'shouldContentComponentBeDeleted()' returns true for it.

		The default implementation simply removes the content from this component,
		and deletes it immediately if 'shouldContentComponentBeDeleted()' returns
		true.
	*/
	virtual void handleContentComponentRemoved (juce::Component* contentRemoved, int index, bool animate);

	/** This function is responsible to making a change in focus apparent. The
		default implementation simply calls refreshLayout().
	*/
	virtual void handleStackFocusChange (juce::Component* newFocusContent, int newIndex, int oldIndex, bool animate);

	/** Helper function to find out if a given content component is supposed
		to be deleted when it is removed. This is specifically required for
		implmenations of handleContentComponentRemoved() (or whatever events
		may happen as a result of that call for a given content component).
	*/
	bool shouldContentComponentBeDeleted (juce::Component* contentComponent);

private:

	juce::Array <juce::WeakReference<juce::Component>> contentComps;
	int stackFocusIndex;
	AutoFocusOrder popAutoFocusOrder;

	juce::ListenerList<StackComponent::Listener> listeners;

};




#endif  // __STACKCOMPONENT_H_695847AD__

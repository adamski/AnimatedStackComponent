/*
  ==============================================================================

    StackNavigationList.h
    Created: 13 Mar 2011 12:37:14pm
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __STACKNAVIGATIONLIST_H_D59A3816__
#define __STACKNAVIGATIONLIST_H_D59A3816__


class StackNavigationList	:	public StackComponent::Controller,
								public juce::ListBoxModel
{
public:

	StackNavigationList ();
	~StackNavigationList ();

	int getNumRows ();
	void paintListBoxItem (int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected);
	void selectedRowsChanged (int lastRowSelected);

	void stackComponentContentChanged (StackComponent* stack);
	void stackComponentFocusChanged (StackComponent* stack);

	static void setContentTitle (juce::Component* content, const juce::String& title);
	static juce::String getContentTitle (juce::Component* content);

	static const juce::Identifier titlePropertyId;

private:

	void selectRowForStackFocus ();

	juce::ListBox listbox;

};



#endif  // __STACKNAVIGATIONLIST_H_D59A3816__

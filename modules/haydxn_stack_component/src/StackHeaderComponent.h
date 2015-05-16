/*
  ==============================================================================

    StackHeaderComponent.h
    Created: 12 Mar 2011 12:29:38pm
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __StackHeaderComponent_H_8C491CB2__
#define __StackHeaderComponent_H_8C491CB2__

#include "StackComponent.h"
#include "MarginedContainerComponent.h"
#include "HeaderLabel.h"


class StackHeaderComponent	:	public StackComponent::Controller,
									public juce::Button::Listener
{
public:

	StackHeaderComponent ();
	virtual ~StackHeaderComponent ();

	void resized ();

	static void setStackContentTitle (juce::Component* contentComponent, const juce::String& contentTitle);
	static juce::String getStackContentTitle (juce::Component* contentComponent);

	void stackComponentContentChanged (StackComponent* stack);
	void stackComponentFocusChanged (StackComponent* stack);

	HeaderLabel& getTitleLabel ();

	void buttonClicked (juce::Button* button);

	static const juce::Identifier contentTitlePropertyId;
	static const char* titleLabelId;

	void setBackButtonPadding (const juce::BorderSize<int>& padding);
	void setBackButtonWidth (int width);

	void refreshTitles ();

private:

	void setBackButtonVisibility (bool showBack);

	MarginedContainerComponent container;

	HeaderLabel titleLabel;
	juce::TextButton backButton;

	juce::BorderSize<int> backButtonPadding;
	int backButtonWidth;
	bool backButtonVisible;
};



#endif  // __StackHeaderComponent_H_8C491CB2__

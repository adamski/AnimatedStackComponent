/*
  ==============================================================================

    StackHeaderComponent.cpp
    Created: 12 Mar 2011 12:29:38pm
    Author:  Haydxn

  ==============================================================================
*/

const Identifier StackHeaderComponent::contentTitlePropertyId ("BasicStackHeader_Title");
const char* StackHeaderComponent::titleLabelId = "Title";

StackHeaderComponent::StackHeaderComponent ()
:	backButtonWidth (60),
	backButtonVisible (false),
	backButtonPadding (5),
	backButton ("Back")
{
	container.setBounds ("0,0,parent.width,parent.height");
	addAndMakeVisible (&container);

	setInterceptsMouseClicks (false,true);

	titleLabel.setComponentID (titleLabelId);
	titleLabel.setInterceptsMouseClicks(false,false);

	container.getBody().addAndMakeVisible (&titleLabel);

	titleLabel.setBounds("0,0,parent.width,parent.height");
	titleLabel.setFont (Font(16,Font::bold));
	titleLabel.setJustification (Justification::centred);
	titleLabel.setPageReferenceComponent (this);

	backButton.addListener (this);
}

StackHeaderComponent::~StackHeaderComponent ()
{
}

void StackHeaderComponent::resized ()
{
}

void StackHeaderComponent::setStackContentTitle (Component* contentComponent, const String& contentTitle)
{
	contentComponent->getProperties().set (contentTitlePropertyId, contentTitle);
}

String StackHeaderComponent::getStackContentTitle (Component* contentComponent)
{
	return contentComponent->getProperties() [contentTitlePropertyId];
}

void StackHeaderComponent::refreshTitles ()
{
	StackComponent* stack = getTargetStack ();
	if (stack != 0)
	{
		Component* c = stack->getStackFocusContent ();
		if (c  != 0)
		{
			String title = getStackContentTitle (c);
			titleLabel.setText (title);
		}
	}
}


void StackHeaderComponent::stackComponentContentChanged (StackComponent* stack)
{
	refreshTitles ();
}

void StackHeaderComponent::stackComponentFocusChanged (StackComponent* stack)
{
	if (stack!= 0)
	{
		refreshTitles ();
	}
	setBackButtonVisibility (stack->getStackFocusIndex() > 0);
}

void StackHeaderComponent::setBackButtonVisibility (bool showBack)
{
	if (backButtonVisible != showBack)
	{
		if (showBack)
		{
			container.setLeftMarginContent (&backButton, backButtonWidth, backButtonPadding);
		}
		else
		{
			container.clearLeftMargin (false);
		}

		backButtonVisible = showBack;
	}
}

void StackHeaderComponent::setBackButtonWidth (int width)
{
	backButtonWidth = width;
	if (backButtonVisible)
	{
		container.setLeftMarginWidth (width);
	}
}

void StackHeaderComponent::setBackButtonPadding (const BorderSize<int>& padding)
{
	backButtonPadding = padding;
	if (backButtonVisible)
	{
		container.clearLeftMargin (false);
		container.setLeftMarginContent (&backButton, backButtonWidth, backButtonPadding);
	}
}

void StackHeaderComponent::buttonClicked (Button* button)
{
	if (button == &backButton)
	{
		StackComponent* stack = getTargetStack ();
		if (stack != 0)
		{
			int i = stack->getStackFocusIndex ();
			stack->popComponentsAboveIndex (i-1);
		}
	}
}


/*
  ==============================================================================

    AnimatedStackPanel.cpp
    Created: 13 Mar 2011 10:53:12am
    Author:  Haydxn

  ==============================================================================
*/

#include "AnimatedStackPanel.h"
#include "AnimatedListBox.h"

AnimatedStackPanel::AnimatedStackPanel (const ValueTree& data)
:	data (data)
{
	setOpaque (true);

	StackHeaderComponent::setStackContentTitle (this, data.getType().toString());
	StackNavigationList::setContentTitle (this, data.getType().toString());
}

AnimatedStackPanel::~AnimatedStackPanel ()
{
}

void AnimatedStackPanel::paint (Graphics& g)
{
	g.fillAll (Colours::grey);
}

AnimatedStackComponent* AnimatedStackPanel::getStack ()
{
	return static_cast<AnimatedStackComponent*> (StackComponent::findForContent (this));
}

void AnimatedStackPanel::pushAfter (Component* newComponent, bool autoFocus, bool animate)
{
	StackComponent* stack = getStack();
	if (stack != 0)
	{
		stack->pushAfterExisting (this, newComponent, true, autoFocus, animate);
	}
}

void AnimatedStackPanel::pop ()
{
	StackComponent* stack = getStack();
	if (stack != 0)
	{
		int index = stack->indexOfContentComponent (this);
		stack->popComponentsAboveIndex (index-1);
	}
}

/*
void AnimatedStackPanel::valueTreeListBoxItemDoubleClicked (ValueTreeListBox* source, const MouseEvent& e, int index, const ValueTree& itemNode)
{
    AnimatedStackPanel* nextPanel = new AnimatedStackPanel (itemNode);
    if (index == 1)
    {
        Rectangle<int> rowPosition = source->getListBox().getRowPosition(index, false);
        ShutterAnimator::Ptr shutterAnimator = new ShutterAnimator(rowPosition, 300, 0.5, 1.0);
        shutterAnimator->setStackComponent(getStack());
        AnimatedStackHelpers::setStackAnimatorForComponent(shutterAnimator, nextPanel);
    }
    pushAfter (nextPanel,true,true);
}
*/



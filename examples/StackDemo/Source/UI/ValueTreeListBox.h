/*
  ==============================================================================

    ValueTreeListBox.h
    Created: 13 Mar 2011 11:39:27am
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __VALUETREELISTBOX_H_E3E9EB36__
#define __VALUETREELISTBOX_H_E3E9EB36__

#include "../../JuceLibraryCode/JuceHeader.h"

class ValueTreeListBox	:	public Component,
							public ValueTree::Listener,
							public ListBoxModel
{
public:

	ValueTreeListBox ();
	virtual ~ValueTreeListBox ();

	/////////////////////////////////////////////////////////////////

	class ItemComponent	:	public Component
	{
	public:

		ItemComponent (ValueTreeListBox* parent);

		ValueTree getNode ();
		void setNode (const ValueTree& node);
		virtual void nodeAssigned (const ValueTree& node);

		void paint (Graphics& g);

		bool isSelected ();
		void setSelected (bool shouldBeSelected);
		virtual void selectednessChanged ();

		ValueTreeListBox* getOwner () const;

	private:

		friend class ValueTreeListBox;

		ValueTreeListBox* owner;
		ValueTree node;
		bool selected;
	};

	/////////////////////////////////////////////////////////////////

	class Listener
	{
	public:

		virtual void valueTreeListBoxItemDoubleClicked (ValueTreeListBox* source, const MouseEvent& e, int index, const ValueTree& itemNode) = 0;
		virtual void valueTreeListBoxItemClicked (ValueTreeListBox* source, const MouseEvent& e, int index, const ValueTree& itemNode) = 0;
		virtual void valueTreeListBoxContextNodeAssigned (ValueTreeListBox* source, const ValueTree& newContextNode);
	};

	void addListener (Listener* listener);
	void removeListener (Listener* listener);

	/////////////////////////////////////////////////////////////////

	void resized ();

	/////////////////////////////////////////////////////////////////

	void setContextNode (const ValueTree& newNode);
	ValueTree getContextNode ();
	virtual void contextNodeAssigned (const ValueTree& newNode);

	virtual int getNumRows ();
	virtual ValueTree getValueTreeForRow (int rowIndex);
	virtual ItemComponent* createItemComponent ();

	/////////////////////////////////////////////////////////////////

	void refresh ();

	// Implementing ValueTree::Listener
        void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& prop);
        void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded);
        void valueTreeChildRemoved (ValueTree& parentTree,
                                    ValueTree& childWhichHasBeenRemoved,
                                    int indexFromWhichChildWasRemoved);
        void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved,
                                         int oldIndex, int newIndex);
        void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged);

	// Implementing ListBoxModel
	void paintListBoxItem (int rowNumber, Graphics& g, int w, int h, bool selected);
	Component* refreshComponentForRow (int rowNumber, bool selected, Component* existing);
	void listBoxItemClicked (int row, const MouseEvent &e);
	void listBoxItemDoubleClicked (int row, const MouseEvent &e);
	ListBox& getListBox ();

	virtual void itemNodeChanged (int row, ItemComponent* comp, const ValueTree& newNode);

private:

	void changeItemNode (int row, Component* comp, const ValueTree& newNode);

	ValueTree contextNode;
	MarkerList xMarkers;
	ListBox listBox;
	ListenerList<ValueTreeListBox::Listener> listeners;
};


#endif  // __VALUETREELISTBOX_H_E3E9EB36__

/*
  ==============================================================================

    HeaderLabel.h
    Created: 12 Mar 2011 10:04:48pm
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __HEADERLABEL_H_9D129C3__
#define __HEADERLABEL_H_9D129C3__

#include "../../JuceLibraryCode/JuceHeader.h"

/** Less functionality than a Label, but slightly more complex in how
	it handles the positioning of horizontally centred text. This class 
	takes a reference 'page' component, which defines the area the text 
	is intended to be justified within - albeit constricted to its own 
	bounds. It's easier to understand if you see it do its thing!
*/
class HeaderLabel	:	public Component,
						public Value::Listener
{
public:

	HeaderLabel ();
	virtual ~HeaderLabel ();

	void resized ();
	void paint (Graphics& g);

	void setPageReferenceComponent (Component* page);
	Component* getPageReferenceComponent () const;

	void setFont (const Font& font);
	Font getFont () const;

	void setBorderSize (const BorderSize<int> border);
	const BorderSize<int>& getBorderSize () const;

	void setJustification (const Justification& justification);
	Justification getJustification () const;

	void setText (const String& text);
	void setTextValue (const Value& text);
	String getText () const;
	Value getTextValue () const;

	void valueChanged (Value& value);

	static const int textColourId;

private:

	void textPropertiesChanged ();

	WeakReference<Component> pageComponent;
	Font font;
	Justification just;
	Value textValue;
	BorderSize<int> padding;
};


#endif  // __HEADERLABEL_H_9D129C3__

/*
  ==============================================================================

    HeaderLabel.h
    Created: 12 Mar 2011 10:04:48pm
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __HEADERLABEL_H_9D129C3__
#define __HEADERLABEL_H_9D129C3__

/** Less functionality than a Label, but slightly more complex in how
	it handles the positioning of horizontally centred text. This class 
	takes a reference 'page' component, which defines the area the text 
	is intended to be justified within - albeit constricted to its own 
	bounds. It's easier to understand if you see it do its thing!
*/
class HeaderLabel	:	public juce::Component,
						public juce::Value::Listener
{
public:

	HeaderLabel ();
	virtual ~HeaderLabel ();

	void resized ();
    void paint (juce::Graphics& g);

    void setPageReferenceComponent (juce::Component* page);
    juce::Component* getPageReferenceComponent () const;

	void setFont (const juce::Font& font);
	juce::Font getFont () const;

	void setBorderSize (const juce::BorderSize<int> border);
	const juce::BorderSize<int>& getBorderSize () const;

    void setJustification (const juce::Justification& justification);
	juce::Justification getJustification () const;

	void setText (const juce::String& text);
	void setTextValue (const juce::Value& text);
	juce::String getText () const;
	juce::Value getTextValue () const;

	void valueChanged (juce::Value& value);

	static const int textColourId;

private:

	void textPropertiesChanged ();

	juce::WeakReference<juce::Component> pageComponent;
	juce::Font font;
	juce::Justification just;
	juce::Value textValue;
	juce::BorderSize<int> padding;
};



#endif  // __HEADERLABEL_H_9D129C3__

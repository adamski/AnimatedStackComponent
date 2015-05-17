/*
  ==============================================================================

    HeaderLabel.cpp
    Created: 12 Mar 2011 10:04:48pm
    Author:  Haydxn

  ==============================================================================
*/

const int HeaderLabel::textColourId = 0x12019;

HeaderLabel::HeaderLabel ()
:	font (16,Font::bold),
	just (Justification::centred),
	padding (5)
{
	textValue.addListener (this);
	setColour (textColourId,Colours::black);
}

HeaderLabel::~HeaderLabel ()
{
	textValue.removeListener(this);
}


void HeaderLabel::resized ()
{
	textPropertiesChanged ();
}

void HeaderLabel::paint (Graphics& g)
{
	Rectangle<int> textRect (getLocalBounds());

	String text = getText();
	if (just.getOnlyHorizontalFlags() & Justification::horizontallyCentred)
	{
		Component* page = pageComponent.get ();
		if (page)
		{
			int pw = page->getWidth();
			int ph = page->getHeight();
			int x = 0;
			int y = 0;
			int w = jmin(font.getStringWidth(text) + padding.getLeftAndRight(), getWidth() - padding.getLeftAndRight());
			int h = getHeight() - padding.getTopAndBottom();

			just.applyToRectangle (x,y,w,h,0,0,pw,ph);

			textRect = Rectangle<int>(x,y,w,h);
			textRect = textRect.getIntersection (page->getLocalArea(this,padding.subtractedFrom(getLocalBounds())));
			textRect = getLocalArea (page,textRect);

			if (textRect.getWidth() < w)
				textRect.setWidth(w);
		}
	}

	padding.subtractFrom (textRect);
	g.setFont (font);
	g.setColour (findColour(textColourId));
	g.drawFittedText (text,textRect.getX(),textRect.getY(),textRect.getWidth(),textRect.getHeight(),just,1);
}

void HeaderLabel::setPageReferenceComponent (Component* page)
{
	pageComponent = page;
	textPropertiesChanged ();
}

Component* HeaderLabel::getPageReferenceComponent () const
{
	return pageComponent.get();
}

void HeaderLabel::setFont (const Font& font_)
{
	font = font_;
	textPropertiesChanged ();
}

Font HeaderLabel::getFont () const
{
	return font;
}

void HeaderLabel::setBorderSize (const BorderSize<int> border)
{
	padding = border;
	textPropertiesChanged ();
}

const BorderSize<int>& HeaderLabel::getBorderSize () const
{
	return padding;
}

void HeaderLabel::setJustification (const Justification& justification)
{
	just = justification;
	textPropertiesChanged ();
}

Justification HeaderLabel::getJustification () const
{
	return just;
}

void HeaderLabel::setText (const String& text)
{
	textValue.referTo (Value(text));
	textPropertiesChanged ();
}

void HeaderLabel::setTextValue (const Value& text)
{
	textValue.referTo (text);
	textPropertiesChanged ();
}

String HeaderLabel::getText () const
{
	return textValue.toString();
}

Value HeaderLabel::getTextValue () const
{
	return textValue;
}

void HeaderLabel::valueChanged (Value& value)
{
	textPropertiesChanged ();
}


void HeaderLabel::textPropertiesChanged ()
{
	repaint ();
}

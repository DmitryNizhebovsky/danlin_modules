/*
  ==============================================================================

    RemixIcon.h
    Created: 17 Apr 2020
    Authors:  Daniel Lindenfelser, Dmitry Nizhebovsky

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
#include "Icons.h"
#include "..\data\RemixIconData.h"

using RenderedIcon = juce::Image;

class RemixIcon {
public:
    static RemixIcon& getInstance();
    
    RenderedIcon getIcon(Icon icon, float size, juce::Colour colour, float scaleFactor = 1.0f);
    RenderedIcon getRotatedIcon(Icon icon, float size, juce::Colour colour, float iconRotation, float scaleFactor = 1.0f);

    void drawAt(juce::Graphics &g, RenderedIcon icon, int x, int y, float scaleFactor = 1.0f);
    void drawCenterdAt(juce::Graphics &g, RenderedIcon icon, juce::Rectangle<int> r, float scaleFactor = 1.0f);
    
    juce::Font getFont();
    juce::Font getFont(float size);
    
    static void drawAt(juce::Graphics &g, Icon icon, float size, juce::Colour colour, int x, int y, float scaleFactor);
    static void drawCenterd(juce::Graphics &g, Icon icon, float size, juce::Colour colour, juce::Rectangle<int> r, float scaleFactor);
    
    static void drawAt(juce::Graphics &g, Icon icon, float size, juce::Colour colour, int x, int y);
    static void drawCenterd(juce::Graphics &g, Icon icon, float size, juce::Colour colour, juce::Rectangle<int> r);
    
    static void drawAtRotated(juce::Graphics &g, Icon icon, float size, juce::Colour colour, int x, int y, float rotation, float scaleFactor);
    static void drawCenterdRotated(juce::Graphics &g, Icon icon, float size, juce::Colour colour, juce::Rectangle<int> r, float rotation, float scaleFactor);

    static void drawAtRotated(juce::Graphics &g, Icon icon, float size, juce::Colour colour, int x, int y, float rotation);
    static void drawCenterdRotated(juce::Graphics &g, Icon icon, float size, juce::Colour colour, juce::Rectangle<int> r, float rotation);

private:
    RemixIcon() {};
    ~RemixIcon() {};
    
private:
    juce::Typeface::Ptr RemixIcon_ptr = juce::Typeface::createSystemTypefaceFor(RemixIconData::remixiconwebfont_ttf, RemixIconData::remixiconwebfont_ttfSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RemixIcon)
};
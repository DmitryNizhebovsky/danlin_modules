/*
  ==============================================================================

    RemixIcon.cpp
    Created: 17 Apr 2020
    Authors:  Daniel Lindenfelser, Dmitry Nizhebovsky

  ==============================================================================
*/

#include "RemixIcon.h"

RemixIcon& RemixIcon::getInstance()
{
    static RemixIcon instance;
    return instance;
}

RenderedIcon RemixIcon::getIcon(Icon icon, float size, juce::Colour colour, float scaleFactor) {
    int scaledSize = int(size * scaleFactor);
    
    String identifier = juce::String(icon + "@" + String(scaledSize) + "@" + colour.toString());
    int64 hash = identifier.hashCode64();
    Image canvas = juce::ImageCache::getFromHashCode(hash);
    if (canvas.isValid())
        return canvas;

    Font RemixIcon = getFont((float)scaledSize);
    scaledSize = std::max(RemixIcon.getStringWidth(icon), scaledSize);
    
    canvas = Image(Image::PixelFormat::ARGB, scaledSize, scaledSize, true);
    Graphics g(canvas);
    g.setColour(colour);
    g.setFont(RemixIcon);
    g.drawText(icon, 0, 0, scaledSize, scaledSize, Justification::centred, true);
    juce::ImageCache::addImageToCache(canvas, hash);
    return canvas;
}

RenderedIcon RemixIcon::getRotatedIcon(Icon icon, float size, juce::Colour colour, float iconRotation, float scaleFactor) {
    int scaledSize = int(size * scaleFactor);
    String identifier = String(icon + "@" + String(scaledSize) + "@" + colour.toString() + "@" + String(iconRotation) + "@");
    int64 hash = identifier.hashCode64();
    Image canvas = juce::ImageCache::getFromHashCode(hash);
    if (canvas.isValid())
        return canvas;

    RenderedIcon renderdIcon = getIcon(icon, size, colour, scaleFactor);
    canvas = Image(Image::PixelFormat::ARGB, renderdIcon.getWidth(), renderdIcon.getHeight(), true);
    Graphics g(canvas);
    g.drawImageTransformed(renderdIcon, AffineTransform::rotation(-(float_Pi * iconRotation), renderdIcon.getWidth() * 0.5f, renderdIcon.getHeight() * 0.5f));
    juce::ImageCache::addImageToCache(canvas, hash);
    return canvas;
}

void RemixIcon::drawAt(juce::Graphics &g, RenderedIcon icon, int x, int y, float scaleFactor) {
    int w = icon.getWidth();
    int h = icon.getHeight();
    g.drawImage(icon,
                x, y,
                (int)(w/scaleFactor), (int)(h/scaleFactor),
                0, 0,
                w, h,
                false);
}

void RemixIcon::drawCenterdAt(juce::Graphics &g, RenderedIcon icon, Rectangle<int> r, float scaleFactor) {
    float iconWidth = icon.getWidth() / scaleFactor;
    float iconHeight = icon.getHeight() / scaleFactor;
    
    int x = r.getX() + (int)((r.getWidth() * 0.5f) - (iconWidth * 0.5f));
    int y = r.getY() + (int)((r.getHeight() * 0.5f) - (iconHeight * 0.5f));
    g.drawImage(icon, x, y, (int)iconWidth, (int)iconHeight, 0, 0, icon.getWidth(), icon.getWidth());
}

juce::Font RemixIcon::getFont() {
    static Font RemixIconFont(RemixIcon_ptr);
    return RemixIconFont;
}

juce::Font RemixIcon::getFont(float size) {
    juce::Font font = getFont();
    font.setHeight(size);
    return font;
}

void RemixIcon::drawAt(juce::Graphics &g, Icon icon, float size, juce::Colour colour, int x, int y, float scaleFactor) {
    RemixIcon::getInstance().drawAt(g, RemixIcon::getInstance().getIcon(icon, size, colour, scaleFactor), x, y, scaleFactor);
}

void RemixIcon::drawAt(juce::Graphics &g, Icon icon, float size, juce::Colour colour, int x, int y) {
    RemixIcon::getInstance().drawAt(g, RemixIcon::getInstance().getIcon(icon, size, colour, g.getInternalContext().getPhysicalPixelScaleFactor()), x, y, g.getInternalContext().getPhysicalPixelScaleFactor());
}

void RemixIcon::drawCenterd(juce::Graphics &g, Icon icon, float size, juce::Colour colour, juce::Rectangle<int> r, float scaleFactor) {
    RemixIcon::getInstance().drawCenterdAt(g, RemixIcon::getInstance().getIcon(icon, size, colour, scaleFactor), r, scaleFactor);
}

void RemixIcon::drawCenterd(juce::Graphics &g, Icon icon, float size, juce::Colour colour, juce::Rectangle<int> r) {
    RemixIcon::getInstance().drawCenterdAt(g, RemixIcon::getInstance().getIcon(icon, size, colour, g.getInternalContext().getPhysicalPixelScaleFactor()), r,  g.getInternalContext().getPhysicalPixelScaleFactor());
}

void RemixIcon::drawAtRotated(juce::Graphics &g, Icon icon, float size, juce::Colour colour, int x, int y, float rotation, float scaleFactor) {
    RemixIcon::getInstance().drawAt(g, RemixIcon::getInstance().getRotatedIcon(icon, size, colour, rotation, scaleFactor), x, y, scaleFactor);
}

void RemixIcon::drawAtRotated(juce::Graphics &g, Icon icon, float size, juce::Colour colour, int x, int y, float rotation) {
    RemixIcon::getInstance().drawAt(g, RemixIcon::getInstance().getRotatedIcon(icon, size, colour, rotation, g.getInternalContext().getPhysicalPixelScaleFactor()), x, y, g.getInternalContext().getPhysicalPixelScaleFactor());
}

void RemixIcon::drawCenterdRotated(juce::Graphics &g, Icon icon, float size, juce::Colour colour, juce::Rectangle<int> r, float rotation, float scaleFactor) {
    RemixIcon::getInstance().drawCenterdAt(g, RemixIcon::getInstance().getRotatedIcon(icon, size, colour, rotation, scaleFactor), r, scaleFactor);
}

void RemixIcon::drawCenterdRotated(juce::Graphics &g, Icon icon, float size, juce::Colour colour, juce::Rectangle<int> r, float rotation) {
    RemixIcon::getInstance().drawCenterdAt(g, RemixIcon::getInstance().getRotatedIcon(icon, size, colour, rotation, g.getInternalContext().getPhysicalPixelScaleFactor()), r, g.getInternalContext().getPhysicalPixelScaleFactor());
}
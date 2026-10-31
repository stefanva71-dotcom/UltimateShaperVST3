#include "PluginProcessor.h"
#include "PluginEditor.h"

UltimateShaperAudioProcessorEditor::UltimateShaperAudioProcessorEditor(
    UltimateShaperAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(760, 500);
}

UltimateShaperAudioProcessorEditor::~UltimateShaperAudioProcessorEditor()
{
}

void UltimateShaperAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(22, 24, 31));

    g.setColour(juce::Colours::white);
    g.setFont(28.0f);
    g.drawText("ULTIMATE SHAPER", 20, 15, 720, 45,
               juce::Justification::centred);

    g.setColour(juce::Colour(120, 125, 140));
    g.setFont(15.0f);
    g.drawText("RHYTHMIC VOLUME SHAPER", 20, 60, 720, 25,
               juce::Justification::centred);

    juce::Rectangle<int> area(40, 110, 680, 300);

    g.setColour(juce::Colour(38, 42, 52));
    g.fillRoundedRectangle(area.toFloat(), 8.0f);

    g.setColour(juce::Colour(65, 70, 85));

    for (int i = 1; i < 16; ++i)
    {
        float x = area.getX() + area.getWidth() * i / 16.0f;
        g.drawVerticalLine((int)x, (float)area.getY(),
                           (float)area.getBottom());
    }

    for (int i = 1; i < 8; ++i)
    {
        float y = area.getY() + area.getHeight() * i / 8.0f;
        g.drawHorizontalLine((int)y, (float)area.getX(),
                             (float)area.getRight());
    }

    juce::Path curve;

    for (int i = 0; i < 16; ++i)
    {
        float x = area.getX() + area.getWidth() * i / 15.0f;
        float y = area.getBottom()
                - audioProcessor.volumeCurve[i] * area.getHeight();

        if (i == 0)
            curve.startNewSubPath(x, y);
        else
            curve.lineTo(x, y);
    }

    g.setColour(juce::Colour(0, 210, 170));
    g.strokePath(curve, juce::PathStrokeType(3.0f));

    g.setFont(16.0f);
    g.setColour(juce::Colours::white);
    g.drawText("16 STEPS  |  140 BPM", 40, 435, 680, 30,
               juce::Justification::centred);
}

void UltimateShaperAudioProcessorEditor::resized()
{
}


#include "PluginProcessor.h"
#include "PluginEditor.h"

UltimateShaperAudioProcessorEditor::UltimateShaperAudioProcessorEditor(
    UltimateShaperAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(760, 540);

    resetButton.onClick = [this]
    {
        resetCurve();
    };

    addAndMakeVisible(resetButton);

    syncButton.setToggleState(true, juce::dontSendNotification);
    addAndMakeVisible(syncButton);

    bpmLabel.setText("TEMPO: HOST SYNC", juce::dontSendNotification);
    bpmLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    bpmLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(bpmLabel);
}

UltimateShaperAudioProcessorEditor::~UltimateShaperAudioProcessorEditor()
{
}

void UltimateShaperAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(18, 20, 27));

    g.setColour(juce::Colours::white);
    g.setFont(28.0f);
    g.drawText("ULTIMATE SHAPER", 20, 15, 720, 45,
               juce::Justification::centred);

    g.setColour(juce::Colour(120, 125, 140));
    g.setFont(15.0f);
    g.drawText("RHYTHMIC VOLUME SHAPER", 20, 60, 720, 25,
               juce::Justification::centred);

    juce::Rectangle<float> area(40.0f, 110.0f, 680.0f, 300.0f);

    g.setColour(juce::Colour(35, 39, 49));
    g.fillRoundedRectangle(area, 8.0f);

    g.setColour(juce::Colour(60, 65, 78));

    for (int i = 1; i < 16; ++i)
    {
        float x = area.getX() + area.getWidth() * i / 16.0f;
        g.drawVerticalLine((int)x, area.getY(), area.getBottom());
    }

    for (int i = 1; i < 8; ++i)
    {
        float y = area.getY() + area.getHeight() * i / 8.0f;
        g.drawHorizontalLine((int)y, area.getX(), area.getRight());
    }

    juce::Path curve;

    for (int i = 0; i < 16; ++i)
    {
        float x = area.getX() + area.getWidth() * i / 16.0f;
        float y = area.getBottom()
                - audioProcessor.volumeCurve[i] * area.getHeight();

        if (i == 0)
            curve.startNewSubPath(x, y);
        else
            curve.lineTo(x, y);
    }

    curve.lineTo(area.getRight(),
                 area.getBottom()
                 - audioProcessor.volumeCurve[0] * area.getHeight());

    g.setColour(juce::Colour(0, 210, 170));
    g.strokePath(curve, juce::PathStrokeType(3.0f));
}

void UltimateShaperAudioProcessorEditor::updateCurveFromMouse(float x, float y)
{
    const float left = 40.0f;
    const float top = 110.0f;
    const float width = 680.0f;
    const float height = 300.0f;

    if (x < left || x > left + width || y < top || y > top + height)
        return;

    int index = juce::jlimit(0, 15, (int)((x - left) / width * 16.0f));

    float value = 1.0f - (y - top) / height;

    audioProcessor.volumeCurve[index] = juce::jlimit(0.0f, 1.0f, value);

    repaint();
}

void UltimateShaperAudioProcessorEditor::mouseDown(const juce::MouseEvent& event)
{
    updateCurveFromMouse((float)event.x, (float)event.y);
}

void UltimateShaperAudioProcessorEditor::mouseDrag(const juce::MouseEvent& event)
{
    updateCurveFromMouse((float)event.x, (float)event.y);
}

void UltimateShaperAudioProcessorEditor::resetCurve()
{
    audioProcessor.volumeCurve.fill(1.0f);
    repaint();
}

void UltimateShaperAudioProcessorEditor::resized()
{
    resetButton.setBounds(40, 455, 150, 35);
    syncButton.setBounds(220, 455, 100, 35);
    bpmLabel.setBounds(400, 455, 320, 35);
}

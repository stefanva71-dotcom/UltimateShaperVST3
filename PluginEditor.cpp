
#include "PluginProcessor.h"
#include "PluginEditor.h"

UltimateShaperAudioProcessorEditor::UltimateShaperAudioProcessorEditor(
    UltimateShaperAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(700, 450);
}

UltimateShaperAudioProcessorEditor::~UltimateShaperAudioProcessorEditor() {}

void UltimateShaperAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(25, 25, 32));

    g.setColour(juce::Colours::white);
    g.setFont(28.0f);
    g.drawText("ULTIMATE SHAPER", 20, 20, 660, 50,
        juce::Justification::centred);

    g.setFont(16.0f);
    g.drawText("Rhythmic Volume Shaper", 20, 80, 660, 30,
        juce::Justification::centred);
}

void UltimateShaperAudioProcessorEditor::resized()
{
}


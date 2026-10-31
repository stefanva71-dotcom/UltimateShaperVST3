#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class UltimateShaperAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit UltimateShaperAudioProcessorEditor(UltimateShaperAudioProcessor&);
    ~UltimateShaperAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;

private:
    UltimateShaperAudioProcessor& audioProcessor;

    void updateCurveFromMouse(float x, float y);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UltimateShaperAudioProcessorEditor)
};

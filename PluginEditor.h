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

private:
    UltimateShaperAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UltimateShaperAudioProcessorEditor)
};

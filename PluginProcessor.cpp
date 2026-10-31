
#include "PluginProcessor.h"
#include "PluginEditor.h"

UltimateShaperAudioProcessor::UltimateShaperAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

UltimateShaperAudioProcessor::~UltimateShaperAudioProcessor() {}

void UltimateShaperAudioProcessor::prepareToPlay(double, int) {}
void UltimateShaperAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool UltimateShaperAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}
#endif

void UltimateShaperAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
}

juce::AudioProcessorEditor* UltimateShaperAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

bool UltimateShaperAudioProcessor::hasEditor() const { return true; }
const juce::String UltimateShaperAudioProcessor::getName() const { return JucePlugin_Name; }
bool UltimateShaperAudioProcessor::acceptsMidi() const { return false; }
bool UltimateShaperAudioProcessor::producesMidi() const { return false; }
bool UltimateShaperAudioProcessor::isMidiEffect() const { return false; }
double UltimateShaperAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int UltimateShaperAudioProcessor::getNumPrograms() { return 1; }
int UltimateShaperAudioProcessor::getCurrentProgram() { return 0; }
void UltimateShaperAudioProcessor::setCurrentProgram(int) {}
const juce::String UltimateShaperAudioProcessor::getProgramName(int) { return {}; }
void UltimateShaperAudioProcessor::changeProgramName(int, const juce::String&) {}

void UltimateShaperAudioProcessor::getStateInformation(juce::MemoryBlock&) {}
void UltimateShaperAudioProcessor::setStateInformation(const void*, int) {}


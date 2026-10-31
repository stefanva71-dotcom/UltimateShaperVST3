
#include "PluginProcessor.h"
#include "PluginEditor.h"

UltimateShaperAudioProcessor::UltimateShaperAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

UltimateShaperAudioProcessor::~UltimateShaperAudioProcessor()
{
}

void UltimateShaperAudioProcessor::prepareToPlay(double sampleRate, int)
{
    currentSampleRate = sampleRate;
    phase = 0.0;
}

void UltimateShaperAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool UltimateShaperAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}
#endif

float UltimateShaperAudioProcessor::getVolumeAtPhase(float p) const
{
    p = juce::jlimit(0.0f, 0.999999f, p);

    float position = p * 16.0f;
    int index = (int)position;
    float fraction = position - index;

    float a = volumeCurve[index];
    float b = volumeCurve[(index + 1) % 16];

    return a + (b - a) * fraction;
}

void UltimateShaperAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    double bpm = 140.0;

    if (auto* playHead = getPlayHead())
    {
        if (auto position = playHead->getPosition())
        {
            if (auto hostBpm = position->getBpm())
                bpm = *hostBpm;

            if (auto ppq = position->getPpqPosition())
            {
                phase = std::fmod(*ppq, 1.0);

                if (phase < 0.0)
                    phase += 1.0;
            }
        }
    }

    bpm = juce::jlimit(20.0, 300.0, bpm);

    const double cycleLength = 60.0 / bpm;

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        float gain = getVolumeAtPhase((float)phase);

        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            buffer.setSample(
                channel,
                sample,
                buffer.getSample(channel, sample) * gain
            );
        }

        phase += 1.0 / (currentSampleRate * cycleLength);

        if (phase >= 1.0)
            phase -= 1.0;
    }
}

juce::AudioProcessorEditor* UltimateShaperAudioProcessor::createEditor()
{
    return new UltimateShaperAudioProcessorEditor(*this);
}

bool UltimateShaperAudioProcessor::hasEditor() const { return true; }

const juce::String UltimateShaperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

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

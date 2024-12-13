
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class OscilloscopeAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    OscilloscopeAudioProcessorEditor (OscilloscopeAudioProcessor&);
    ~OscilloscopeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OscilloscopeAudioProcessor& audioProcessor;
    void timerCallback() final {
        repaint();
    }
    Image background = ImageCache::getFromMemory(BinaryData::oscilloscope_bg_png, BinaryData::oscilloscope_bg_pngSize);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscilloscopeAudioProcessorEditor)
};

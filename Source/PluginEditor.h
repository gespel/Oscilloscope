
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class OscilloscopeAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer, public juce::Slider::Listener
{
public:
    OscilloscopeAudioProcessorEditor (OscilloscopeAudioProcessor&);
    ~OscilloscopeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    juce::Slider gain;
    juce::Slider windowSize;

private:
    int sample_increase = 1;
    double gain_value = 1;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OscilloscopeAudioProcessor& audioProcessor;
    void timerCallback() final {
        repaint();
    }
    void sliderValueChanged(juce::Slider* slider) override;
    Image background = ImageCache::getFromMemory(BinaryData::oscilloscope_bg_png, BinaryData::oscilloscope_bg_pngSize);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscilloscopeAudioProcessorEditor)
};

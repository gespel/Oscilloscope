#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OscilloscopeAudioProcessorEditor::OscilloscopeAudioProcessorEditor (OscilloscopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (512, 300);
    startTimer(100.0);
}

OscilloscopeAudioProcessorEditor::~OscilloscopeAudioProcessorEditor()
{
}

//==============================================================================
void OscilloscopeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::purple);
    float* data = audioProcessor.getWindow();
    for(int i = 0; i < 512; i++) {
        g.drawLine(i, (data[i]*800) + 150, i+1, (data[i+1]*800) + 150, 2);
    }
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Made by Phi Labs", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void OscilloscopeAudioProcessorEditor::resized()
{

}

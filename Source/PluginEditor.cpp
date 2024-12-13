#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OscilloscopeAudioProcessorEditor::OscilloscopeAudioProcessorEditor (OscilloscopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (512, 406);
    startTimer(100.0);
}

OscilloscopeAudioProcessorEditor::~OscilloscopeAudioProcessorEditor()
{
}

//==============================================================================
void OscilloscopeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
    g.drawImageAt(background, 0, 0);

    g.setColour (juce::Colour(0xaa, 0x76, 0xb4));
    float* data = audioProcessor.getWindow();
    for(int i = 0; i < 474; i++) {
        g.drawLine(i+19, (data[i]*800) + 185, i+20, (data[i+1]*800) + 185, 3);
    }
    g.setFont (juce::FontOptions (11.0f));
    g.drawText("Made by Phi Labs", juce::Rectangle(10, 394, 100, 15), juce::Justification::centred);
    //g.drawFittedText ("Made by Phi Labs", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void OscilloscopeAudioProcessorEditor::resized()
{

}

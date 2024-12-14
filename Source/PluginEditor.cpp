#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//Timer werte zischen ca 20 und 100 sind für ein flüssiges Bild gut. Alles andere ist eher für Analyse praktisch
OscilloscopeAudioProcessorEditor::OscilloscopeAudioProcessorEditor (OscilloscopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (512, 406);
    startTimer(20.0);
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
    for(int i = 0; i < 474; i += 1) {
        g.drawLine(i + 19, (data[i + sample_increase]*800) + 185, i + 20, (data[i + sample_increase + sample_increase]*800) + 185, 3);
    }
    g.setFont (juce::FontOptions (11.0f));
    g.drawText("Made by Phi Labs", juce::Rectangle(11, 308, 100, 15), juce::Justification::centred);
}

void OscilloscopeAudioProcessorEditor::resized()
{

}

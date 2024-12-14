#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//Timer werte zischen ca 20 und 100 sind für ein flüssiges Bild gut. Alles andere ist eher für Analyse praktisch
OscilloscopeAudioProcessorEditor::OscilloscopeAudioProcessorEditor (OscilloscopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (512, 406);
    startTimer(20.0);

    gain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gain.setRange(0.0, 100.0, 0.1);
    gain.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    gain.addListener(this);
    addAndMakeVisible(gain);

    windowSize.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    windowSize.setRange(0.0, 3000.0, 0.1);
    windowSize.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    windowSize.addListener(this);
    addAndMakeVisible(windowSize);
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
        g.drawLine(i + 19, (data[i + sample_increase]*gain_value) + 185, i + 20, (data[i + sample_increase + sample_increase]*gain_value) + 185, 3);
    }
    g.setFont (juce::FontOptions (11.0f));
    g.drawText("Made by Phi Labs", juce::Rectangle(11, 308, 100, 15), juce::Justification::centred);
}

void OscilloscopeAudioProcessorEditor::resized()
{
    gain.setBounds(32, 220, 67, 285);
    //requencyWindow.setBounds();
}

void OscilloscopeAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    gain_value = gain.getValue();
}

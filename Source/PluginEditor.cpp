#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//Timer werte zischen ca 20 und 100 sind für ein flüssiges Bild gut. Alles andere ist eher für Analyse praktisch
OscilloscopeAudioProcessorEditor::OscilloscopeAudioProcessorEditor (OscilloscopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colour(0xca, 0x96, 0xb4));
    setSize (512, 406);
    startTimer(20.0);

    gain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gain.setRange(1.0, 100.0, 0.1);
    gain.setTextValueSuffix(" dB");
    gain.textFromValueFunction = [](double linear)
    {
        double db;

        if (linear != 0.0f)
         db = 20.0f * log10(linear);
        else
         db = -144.0f;

        return "+" + juce::String(db);
    };
    gain.addListener(this);
    addAndMakeVisible(gain);
    
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gain, true);
    addAndMakeVisible(gainLabel);

    windowSize.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    windowSize.setRange(1, 16, 1);
    windowSize.setTextValueSuffix("x");
    windowSize.addListener(this);
    addAndMakeVisible(windowSize);
    
    windowSizeLabel.setText("Window Size", juce::dontSendNotification);
    windowSizeLabel.attachToComponent(&windowSize, true);
    addAndMakeVisible(windowSizeLabel);
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
        g.drawLine(i + 19, (data[i + sample_increase]) + 185, i + 20, (data[i + sample_increase + sample_increase]) + 185, 3);
    }
    g.setFont (juce::FontOptions (11.0f));
    g.drawText("Made by Phi Labs", juce::Rectangle(11, 308, 100, 15), juce::Justification::centred);
    gain.getTextFromValue(gain_value);
}

double OscilloscopeAudioProcessorEditor::linearToDb(double linear)
{
    double db;

    if (linear != 0.0f)
     db = 20.0f * log10(linear);
    else
     db = -144.0f;

    return db;
}

void OscilloscopeAudioProcessorEditor::resized()
{
    gain.setBounds(57, 330, 187, 70);
    windowSize.setBounds(320, 330, 187, 70);
    //requencyWindow.setBounds();
}

void OscilloscopeAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    audioProcessor.gain = gain.getValue();
    gain_value = gain.getValue();
    sample_increase = windowSize.getValue();
}

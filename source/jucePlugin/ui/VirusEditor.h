#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "Virus_Buttons.h"
#include "Virus_LookAndFeel.h"
#include "../VirusController.h"

class VirusParameterBinding;
class OscEditor;
class LfoEditor;
class FxEditor;
class ArpEditor;

class VirusEditor : public juce::Component, private juce::Timer
{
public:
    VirusEditor(VirusParameterBinding& _parameterBinding, Virus::Controller& _controller);
    ~VirusEditor() override;
    void resized() override;
    void changePart(uint8_t _part);
    void updatePartsPresetNames();
    void loadFile();
private:
    void timerCallback() override;

    Buttons::PartSelectButton m_partSelect[16];
    juce::Label m_partLabels[16];
    juce::TextButton m_presetNames[16];
    juce::TextButton m_nextPatch[16];
    juce::TextButton m_prevPatch[16];

    static constexpr auto kPartGroupId = 0x3FBBA;
    struct MainButtons : juce::Component, juce::Value::Listener
    {
        MainButtons();
        void setupButton (int i, std::unique_ptr<juce::Drawable>&& btn, juce::DrawableButton&);
        void valueChanged(juce::Value &) override;

        std::function<void()> updateSection;
        juce::DrawableButton m_oscFilter, m_lfoMatrix, m_effects, m_arpSettings;
        static constexpr auto kMargin = 5;
        static constexpr auto kButtonWidth = 141;
        static constexpr auto kButtonHeight = 26;
        static constexpr auto kGroupId = 0x3FBBA;
    } m_mainButtons;

    struct PresetButtons : juce::Component
    {
        PresetButtons();
        Buttons::PresetButton m_save, m_load, m_presets;
    } m_presetButtons;

    struct PartButtons : juce::Component {
        PartButtons();
    };
    void applyToSections(std::function<void(juce::Component *)>);

    VirusParameterBinding& m_parameterBinding;
    Virus::Controller& m_controller;
    std::unique_ptr<OscEditor> m_oscEditor;
    std::unique_ptr<LfoEditor> m_lfoEditor;
    std::unique_ptr<FxEditor> m_fxEditor;
    std::unique_ptr<ArpEditor> m_arpEditor;

    std::unique_ptr<juce::Drawable> m_background;

    Virus::LookAndFeel m_lookAndFeel;

    juce::String m_previousPath;
};

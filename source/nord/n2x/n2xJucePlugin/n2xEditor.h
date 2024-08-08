#pragma once

#include "jucePluginEditorLib/pluginEditor.h"
#include "jucePluginLib/patchdb/patch.h"

namespace jucePluginEditorLib
{
	class FocusedParameter;
	class Processor;
}

namespace pluginLib
{
	class ParameterBinding;
}

namespace n2xJucePlugin
{
	class FocusedParameter;
	class PatchManager;
	class Controller;

	class Arp;
	class Lcd;
	class MasterVolume;
	class OctLed;
	class Parts;
	class VmMap;

	class Editor final : public jucePluginEditorLib::Editor
	{
	public:
		Editor(jucePluginEditorLib::Processor& _processor, pluginLib::ParameterBinding& _binding, std::string _skinFolder, const std::string& _jsonFilename);
		~Editor() override;

		Editor(Editor&&) = delete;
		Editor(const Editor&) = delete;
		Editor& operator = (Editor&&) = delete;
		Editor& operator = (const Editor&) = delete;

		static const char* findEmbeddedResource(const std::string& _filename, uint32_t& _size);
		const char* findResourceByFilename(const std::string& _filename, uint32_t& _size) override;
		std::pair<std::string, std::string> getDemoRestrictionText() const override;

		Controller& getN2xController() const { return m_controller; }

		genericUI::Button<juce::DrawableButton>* createJuceComponent(genericUI::Button<juce::DrawableButton>*, genericUI::UiObject& _object, const std::string& _name, juce::DrawableButton::ButtonStyle) override;

		std::string getCurrentPatchName() const;

		void onPatchActivated(const pluginLib::patchDB::PatchPtr& _patch, uint32_t _part);

		pluginLib::ParameterBinding& getParameterBinding() const { return m_parameterBinding; }

		Lcd& getLCD() const
		{
			assert(m_lcd);
			return *m_lcd.get();
		}

	private:
		void mouseEnter(const juce::MouseEvent& _ev) override;
		void onBtSave() const;
		void onBtPrev() const;
		void onBtNext() const;
		void setCurrentPatchName(uint8_t _part, const std::string& _name);
		void onSelectedPatchChanged(uint8_t _part, const pluginLib::patchDB::PatchKey& _patchKey);

		Controller& m_controller;
		pluginLib::ParameterBinding& m_parameterBinding;

		std::unique_ptr<Arp> m_arp;
		std::unique_ptr<FocusedParameter> m_focusedParameter;
		std::unique_ptr<Lcd> m_lcd;
		std::unique_ptr<MasterVolume> m_masterVolume;
		std::unique_ptr<OctLed> m_octLed;
		std::unique_ptr<Parts> m_parts;
		std::unique_ptr<VmMap> m_vmMap;

		pluginLib::EventListener<uint8_t> onPartChanged;

		std::array<std::string, 4> m_activePatchNames;

		pluginLib::EventListener<uint32_t, pluginLib::patchDB::PatchKey> m_onSelectedPatchChanged;
	};
}

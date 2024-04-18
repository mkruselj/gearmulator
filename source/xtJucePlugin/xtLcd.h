#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

#include "../jucePluginEditorLib/lcd.h"

class XtLcd final : public jucePluginEditorLib::Lcd
{
public:
	explicit XtLcd(Component& _parent);
	~XtLcd() override;

	void setText(const std::array<uint8_t, 80> &_text);

	bool getOverrideText(std::vector<std::vector<uint8_t>>& _lines) override;
	const uint8_t* getCharacterData(uint8_t _character) const override;

	void setCurrentParameter(const std::string& _name, const std::string& _value);

private:
	std::array<uint8_t, 80> m_currentText;
	std::string m_paramName;
	std::string m_paramValue;
};

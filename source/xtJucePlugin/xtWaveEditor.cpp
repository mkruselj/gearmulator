#include "xtWaveEditor.h"

#include "weTree.h"
#include "weWaveTree.h"
#include "weTablesTree.h"
#include "weControlTree.h"
#include "weGraphFreq.h"
#include "weGraphPhase.h"
#include "weGraphTime.h"

#include "xtEditor.h"

namespace xtJucePlugin
{
	WaveEditor::WaveEditor(Editor& _editor) : ComponentMovementWatcher(this), m_editor(_editor), m_data(_editor.getXtController())
	{
		addComponentListener(this);

		m_data.onWaveChanged.addListener([this](const uint32_t& _waveIndex)
		{
			if(_waveIndex != m_selectedWave)
				return;

			setSelectedWave(_waveIndex, true);
		});
	}

	WaveEditor::~WaveEditor()
	{
		destroy();
		removeComponentListener(this);
	}

	void WaveEditor::initialize()
	{
		auto* waveListParent = m_editor.findComponent("wecWaveList");
		auto* tablesListParent = m_editor.findComponent("wecWavetableList");
		auto* controlListParent = m_editor.findComponent("wecWaveControlTable");
		auto* waveFreqParent = m_editor.findComponent("wecWaveFreq");
		auto* wavePhaseParent = m_editor.findComponent("wecWavePhase");
		auto* waveTimeParent = m_editor.findComponent("wecWaveTime");

		m_waveTree.reset(new WaveTree(*this));
		m_tablesTree.reset(new TablesTree(*this));
		m_controlTree.reset(new ControlTree(*this));

		m_graphFreq.reset(new GraphFreq(*this));
		m_graphPhase.reset(new GraphPhase(*this));
		m_graphTime.reset(new GraphTime(*this));

		waveListParent->addAndMakeVisible(m_waveTree.get());
		tablesListParent->addAndMakeVisible(m_tablesTree.get());
		controlListParent->addAndMakeVisible(m_controlTree.get());

		waveFreqParent->addAndMakeVisible(m_graphFreq.get());
		wavePhaseParent->addAndMakeVisible(m_graphPhase.get());
		waveTimeParent->addAndMakeVisible(m_graphTime.get());

		constexpr auto colourId = juce::TreeView::ColourIds::backgroundColourId;
		const auto colour = m_waveTree->findColour(colourId);
		m_graphFreq->setColour(colourId, colour);
		m_graphPhase->setColour(colourId, colour);
		m_graphTime->setColour(colourId, colour);
	}

	void WaveEditor::destroy()
	{
		m_waveTree.reset();
		m_controlTree.reset();
		m_tablesTree.reset();
		m_graphFreq.reset();
		m_graphPhase.reset();
		m_graphTime.reset();
	}

	void WaveEditor::checkFirstTimeVisible()
	{
		if(isShowing() && !m_wasVisible)
		{
			m_wasVisible = true;
			onFirstTimeVisible();
		}
	}

	void WaveEditor::onFirstTimeVisible()
	{
		m_data.requestData();
	}

	void WaveEditor::onReceiveWave(const pluginLib::MidiPacket::Data& _data, const std::vector<uint8_t>& _msg)
	{
		m_data.onReceiveWave(_data, _msg);
	}

	void WaveEditor::onReceiveTable(const pluginLib::MidiPacket::Data& _data, const std::vector<uint8_t>& _msg)
	{
		m_data.onReceiveTable(_data, _msg);
	}

	void WaveEditor::setSelectedTable(uint32_t _index)
	{
		if(m_selectedTable == _index)
			return;

		m_selectedTable = _index;
		m_controlTree->setTable(_index);
	}

	void WaveEditor::setSelectedWave(const uint32_t _waveIndex, bool _forceRefresh/* = false*/)
	{
		if(m_selectedWave == _waveIndex && !_forceRefresh)
			return;

		m_selectedWave = _waveIndex;

		if(const auto wave = m_data.getWave(_waveIndex))
			m_graphData.set(*wave);
	}
}

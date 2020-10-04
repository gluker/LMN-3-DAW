#include "EditView.h"


EditView::EditView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      edit(e),
      midiCommandManager(mcm),
      stackNavigationController(std::make_unique<app_navigation::StackNavigationController>(new TracksView(edit, midiCommandManager))),
      tempoSettingsView(std::make_unique<TempoSettingsView>(edit, midiCommandManager)),
      mixerView(std::make_unique<MixerView>(edit, midiCommandManager))
{

    addTab(tracksTabName, juce::Colours::transparentBlack, stackNavigationController.get(), true);
    addTab(tempoSettingsTabName, juce::Colours::transparentBlack, tempoSettingsView.get(), true);
    addTab(mixerTabName, juce::Colours::transparentBlack, mixerView.get(), true);

    // hide tab bar
    setTabBarDepth(0);

    midiCommandManager.addListener(this);

    // Set tracks as initial view
    juce::StringArray names = getTabNames();
    int tracksIndex = names.indexOf(tracksTabName);
    setCurrentTabIndex(tracksIndex);

}

EditView::~EditView()
{

    midiCommandManager.removeListener(this);

}


void EditView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void EditView::resized()
{

    juce::TabbedComponent::resized();

}

void EditView::tracksButtonReleased()
{

    if (isShowing())
    {

        stackNavigationController->popToRoot();
        midiCommandManager.setFocusedComponent(stackNavigationController->getTopComponent());
        juce::StringArray tabNames = getTabNames();
        int tracksIndex = tabNames.indexOf(tracksTabName);
        setCurrentTabIndex(tracksIndex);

    }

}

void EditView::tempoSettingsButtonReleased()
{

    if (isShowing())
    {

        midiCommandManager.setFocusedComponent(tempoSettingsView.get());
        juce::StringArray tabNames = getTabNames();
        int tracksIndex = tabNames.indexOf(tempoSettingsTabName);
        setCurrentTabIndex(tracksIndex);

    }

}

void EditView::mixerButtonReleased()
{

    if (isShowing())
    {

        midiCommandManager.setFocusedComponent(mixerView.get());
        juce::StringArray tabNames = getTabNames();
        int mixerIndex = tabNames.indexOf(mixerTabName);
        setCurrentTabIndex(mixerIndex);

    }

}


#include "Settings.h"
#include "HumidMatic.h"

Settings::Settings()
    :SettingsBase(&logger) {
}

void Settings::initializeSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);
    settingsData.hm.targetHumidityHigh = 50;
    settingsData.hm.targetHumidityLow = 40;
}

SettingsData* Settings::getSettings() {
    return &settingsData;
}
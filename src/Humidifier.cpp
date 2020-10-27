#include "HumidMatic.h"
#include <math.h>

Humidifier::Humidifier(uint8_t fanPin, uint8_t pwmPin, uint8_t waterOKPin) {
    _fanPin = fanPin;
    _pwmPin = pwmPin;
    _waterOKPin = waterOKPin;
}

void Humidifier::begin() {
    pinMode(_fanPin, OUTPUT);
    pinMode(_pwmPin, OUTPUT);
    pinMode(_waterOKPin, INPUT);

    stop(true);
}

void Humidifier::loop() {
    if (!waterOK()) {
        logger.log("Stopping due to low water level.");
        stop();
        return;
    } else {
        logger.log("Water level OK.");
    }

    if (tempSensor.getPressure() < 100) {
        logger.log("Temp sensor not ready, skipping humidifier setup.");
        return;
    }

    float humidity = tempSensor.getHumidity();

    if (isRunning) {
        if (humidity >= settings.getSettings()->hm.targetHumidityHigh) {
            logger.log("Humidity above threshold. Stopping.");
            stop();
        }
    } else {
        if (humidity < settings.getSettings()->hm.targetHumidityLow) {
            logger.log("Humidity below threshold. Starting.");
            start();
        }
    }
}

void Humidifier::start() {
    if (isRunning) {
        // Already running.
        return;
    }

    digitalWrite(_fanPin, HIGH);
    digitalWrite(_pwmPin, LOW);

    isRunning = true;
}

void Humidifier::stop(boolean force) {
    if (!isRunning && !force) {
        // Already stopped.
        return;
    }

    digitalWrite(_fanPin, LOW);
    digitalWrite(_pwmPin, HIGH);

    isRunning = false;
}

boolean Humidifier::waterOK() {
    return digitalRead(_waterOKPin) == LOW;
}

boolean Humidifier::isHumidifying() {
    return isRunning;
}
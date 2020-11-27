#pragma once

#include "HumidMatic.h"

class Humidifier {
    public:
        Humidifier(uint8_t fanPin, uint8_t pwmPin, uint8_t waterOKPin);
        void begin();
        void loop();
        bool isHumidifying();
        bool waterOK();
    private:
        void start();
        void stop(boolean force=false);
        void cleanUp();
        
        uint8_t _fanPin;
        uint8_t _pwmPin;
        uint8_t _waterOKPin;

        // State
        boolean isRunning;
        boolean isWaterOK;
};

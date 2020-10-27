#include "HumidMatic.h"
#include "DataCollector.h"

DataCollector::DataCollector():
    InfluxDBCollector(&logger,
                      &wifi,
                      &settings.getSettings()->influxDB,
                      &settings.getSettings()->network) {
}

bool DataCollector::shouldCollect() {
    return tempSensor.getPressure() > 100;
}

void DataCollector::collectData() {
    if (tempSensor.getPressure() > 100) {
        append("temperature", tempSensor.getTemperature(), 2);
        append("humidity", tempSensor.getHumidity(), 1);
        append("abs_humidity", tempSensor.getAbsoluteHimidity(), 2);
        append("pressure", tempSensor.getPressure(), 1);
        append("humidifying", humidifier.isHumidifying()?1:0);

        if (lastPushedHumidity < 0) {
            lastPushedTemp = tempSensor.getTemperature();
            lastPushedHumidity = tempSensor.getHumidity();
        }
        lastTemp = tempSensor.getTemperature();
        lastHumidity = tempSensor.getHumidity();
    }
}

bool DataCollector::shouldPush() {
    if (lastPushedHumidity > 0) {
        if (fabsf(lastPushedTemp - lastTemp) > 1.0) {
            return true;
        }

        if (fabsf(lastPushedHumidity - lastHumidity) > 5.0) {
            return true;
        }
    }

    return false;
}   

void DataCollector::onPush() {
    lastPushedHumidity = lastHumidity;
}
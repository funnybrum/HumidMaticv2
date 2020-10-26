# Humid Matic v2

A humidifier "brain". Use a BME280 sensor to get the humidity and controls the humidifier based on the humidity level.

There is integrated telemetry - collected temperature/humidity/pressure/humidifier stats can be pushed to an InfluxDB.

It has 1 input from a sensor for the humidifier water level. And there are two outputs - PWM for the piezo element driver and for the humidifier fan.

Circuit and PCB is available at https://easyeda.com/funnybrum/humidifier-brain.

## Building the project

The project uses a common set of tools that are availabe in another repo - https://github.com/funnybrum/esp8266-base. Clone the esp8266-base repo in the lib folder:

```
cd lib
git clone git@github.com:funnybrum/esp8266-base.git
```

Actually the changes should become part of the esp8266-base project. This introduces only the required files to enable the development of the POC. Once done all details (base) brum@brum-XPS-13-9370:/brum/dev/HMv2$ 

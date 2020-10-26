#include "HumidMatic.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger, NULL) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));
    server->on("/stats", std::bind(&WebServer::handle_stats, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    bool save = false;

    // Parse passed parameters
    wifi.parse_config_params(this, save);
    dataCollector.parse_config_params(this, save);
    tempSensor.parse_config_params(this, save);

    process_setting("humidity_low", settings.getSettings()->hm.targetHumidityLow, save);
    process_setting("humidity_high", settings.getSettings()->hm.targetHumidityHigh, save);

    // Save settings if necessary
    if (save) {
        settings.save();
    }

    // Generate settings page content
    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);

    char data_collector_settings[strlen_P(INFLUXDB_CONFIG_PAGE) + 96];
    dataCollector.get_config_page(data_collector_settings);

    char temp_sensor_settings[strlen_P(BME280_CONFIG_PAGE) + 16];
    tempSensor.get_config_page(temp_sensor_settings);


    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings,
        data_collector_settings,
        temp_sensor_settings,
        settings.getSettings()->hm.targetHumidityLow,
        settings.getSettings()->hm.targetHumidityHigh);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_get() {
    sprintf_P(buffer,
              GET_JSON,
              tempSensor.getTemperature(),
              tempSensor.getRawTemperature(),
              tempSensor.getHumidity(),
              tempSensor.getRawHumidity(),
              tempSensor.getAbsoluteHimidity(),
              tempSensor.getPressure());
    server->send(200, "application/json", buffer);
}

void WebServer::handle_stats() {
    sprintf_P(buffer,
              PSTR("Uptime: %lus. Free heap: %u"),
              millis()/1000,
              ESP.getFreeHeap());
    server->send(200, "text/plain", buffer);
}

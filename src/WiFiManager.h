#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <string>

class WiFiManager {
public:
    WiFiManager() {}
    bool connectToNetwork(const std::string& ssid);
};

#endif

#include "software_master.h"

// ### Librería de Arduino ###
#include <Arduino.h>

// ######################## Comnicación WiFi ############################
#define ssid "ARGO_ESP32_Master"
#define pass "S0ftware"


class UDP {
public:
  UDP();
};



String getMsg_wifi_rx() {
  String msg_rx = "";
  return msg_rx;
}
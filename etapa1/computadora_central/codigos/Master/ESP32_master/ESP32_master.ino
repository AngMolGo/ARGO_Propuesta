// Proyecto ARGO | ESP32 Master - Carrito

// ### Comunicación UART físico y virtual ###
#include <HardwareSerial.h>
// ### Librería de ARGO_Software

#include "software_master.h"

// ####################### Comunicación UART ############################
// No es necesario declarar Serial1 y Serial2 porque ya se hace en la librería
HardwareSerial Serial3(3);
// Strings para el envío de datos
String msg_rx;  // Mensaje de recepción (Rx)
String msg_tx;  // MEnsaje de transmisión (Tx)

void setup() {
  // ####################### Comunicación UART ############################
  // ### UART 0: Directo a compu, para leer en pruebas ###
  Serial.begin(115200);  // Inicia la comunicación por UART0 (Rx=3, Tx=1)
  // ### UART 1: Sensores ###
  Serial1.begin(9600, SERIAL_8N1, 18, 19);  // Inicia la comunicación por UART1 (Rx=18, Tx=19)
  // ### UART 2: Telecom ###
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // Inicia la comunicación por UART2 (Rx=16, Tx=17)
  // ### UART 3: Motores llantas ###
  Serial3.begin(9600, SERIAL_8N1, 25, 26);  // Inicia la comunicación por UART2 (Rx=25, Tx=26)  

  // ####################### Comunicación WiFi ############################
  
}

void loop() {
  // ####################### Comunicación UART -> (Tx) ############################
  // ### Si el micro de sensores manda información, pasa directamente a telecom. (UART-UART)
  if (Serial1.available()) {
    msg_rx = Serial1.readStringUntil('\n');
    Serial.println("Estoy recibiendo: \"" + msg_rx + "\"...");
    Serial2.println(msg_rx);
  }

  // ######################## Comnicación WiFi -> (Rx) ############################


  delay(50);  // Supuestamente es un sistema embebido, así que después le quitaré este delay.
}
#include <HardwareSerial.h>

String msg_rx;

void setup() {
  
  // ### UART 0: Directo a compu ###
  Serial.begin(115200);                     // Inicia la comunicación por UART0 (Rx=3, Tx=1)
  // ### UART 1: Sensores ###
  Serial1.begin(9600, SERIAL_8N1, 18, 19);  // Inicia la comunicación por UART1 (Rx=18, Tx=19)
  // ### UART 2: Telecom ###
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // Inicia la comunicación por UART2 (Rx=16, Tx=17)
}

void loop() {
  // ### Si el micro de sensores manda información, pasa directamente a telecom. (UART-UART)
  if (Serial1.available()) {
    msg_rx = Serial1.readStringUntil('\n');
    Serial.println("Estoy recibiendo: \"" + msg_rx + "\"...");
    Serial2.println(msg_rx);
  }
  delay(50);
}
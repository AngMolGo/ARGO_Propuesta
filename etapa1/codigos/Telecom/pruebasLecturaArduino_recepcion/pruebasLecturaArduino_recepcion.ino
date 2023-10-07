#include <HardwareSerial.h>

String msg_rx;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                     // Inicia la comunicación por UART0
  Serial2.begin(9600,SERIAL_8N1, 16, 17);  // Inicia la comunicación por UART2
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial2.available()){
    msg_rx = Serial2.readStringUntil('\n');
    Serial.println("Estoy recibiendo: \"" + msg_rx + "\"...");
  }
  delay(50);
}

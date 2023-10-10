#include <HardwareSerial.h>

String msg;
String msg_prueba = "Hola mundo";
void blink(int pin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                     // Inicia la comunicación por UART0
  Serial2.begin(9600,SERIAL_8N1, 16, 17);  // Inicia la comunicación por UART2
  //pinMode(17,OUTPUT);
  //digitalWrite(17, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Estoy enviando: \"" + msg_prueba + "\"...");
  Serial2.println(msg_prueba);
  if(Serial.available()){
    msg_prueba = Serial.readStringUntil('\n');
    Serial.println("Estoy enviando: \"" + msg_prueba + "\"...");
    Serial2.println(msg_prueba);
  }
  delay(500);
}

void loop1(){
  blink(19);
}

void blink(int pin){
  digitalWrite(pin,HIGH);
  delay(3000);
  digitalWrite(pin, LOW);
  delay(3000);
}
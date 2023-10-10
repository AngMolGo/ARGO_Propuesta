#include<RF24.h>
#include<SPI.h>

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Hola mundo");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String msn = Serial.readStringUntil('\n');
    Serial.println("Eco: " + msn);
  }

}

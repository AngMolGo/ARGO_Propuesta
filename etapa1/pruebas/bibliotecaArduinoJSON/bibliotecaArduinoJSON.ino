#include "ARGO_JSON.h"

JsonObject dataSensores = createObjJSON();
JsonObject dataMotores = createObjJSON();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dataSensores["temp"] = 25;
  dataSensores["presion"] = 700;
  dataMotores["comando"] = "adelante";
  dataMotores["vel"] = 10;
}

void loop() {
  // put your main code here, to run repeatedly:

}

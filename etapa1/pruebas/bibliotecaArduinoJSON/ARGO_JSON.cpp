#include "ARGO_JSON.h"

void hola_mundo(){
  Serial.println("Hola mundo :D");
}

JsonObject createObjJSON(){
  DynamicJsonDocument doc(2048);
  JsonObject object = doc.as<JsonObject>();
  return object;
}

String generateMsg(JsonObject obj){
  serializeJson(doc, Serial);
}
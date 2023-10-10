//
//    ARCHIVO: SensorReadings.ino
//    AUTORES: División de Cámaras y Sensores
// AGRUPACIÓN: Proyecto Argo
//    FUNCIÓN: Leer parámetros ambientales e inerciales

// Inclusión de librerías
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "MS5611.h"
#include <Wire.h>
#include <DHT.h>
#include <HardwareSerial.h>

// Creación de objetos
Adafruit_MPU6050 mpu;
MS5611 ms5611(0x77);
DHT dht(4, DHT22);

// Variables para almacenar valores
float temp = 0.0, hum = 0.0, pres = 0.0;

// Métodos para leer parámetros
void get_dht();
//void get_ms();
//void get_imu();

void setup() {

  // Inicializando el puerto Serial a 115200 baudios
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // Inicia la comunicación por UART2

  // Inicializando sensor DHT22
  dht.begin();

  // Inicializando sensor MPU6050
  /*while (!mpu.begin()) {

    Serial.println("MPU6050 no encontrado.");
    delay(2000);
  }


  //Configuración del sensor MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 funcionando correctamente.");
  */
  /*
  // Inicializando sensor MS5611
  if (!ms5611.begin()) {
    Serial.println("MS5611 no encontrado.");
  } else {

    //Configuración del sensor MS5611
    ms5611.setOversampling(OSR_ULTRA_HIGH);

    Serial.println("MS5611 funcionando correctamente.");
  }

  Serial.println("\n");
*/
}


void loop() {

  // Mandando a llamar métodos
  get_dht();
  //get_ms();
  //get_imu();

  Serial.println("");

  delay(2000);
}

// Método para leer temperatura y humedad
void get_dht() {

  temp = dht.readTemperature();
  hum = dht.readHumidity();

  Serial.println("Temperatura ambiente: " + String(temp) + " C");
  Serial2.println("Temperatura ambiente: " + String(temp) + " C");
  Serial.println("Humedad relativa: " + String(hum) + " %RH");
  Serial2.println("Humedad relativa: " + String(hum) + " %RH");
}
/*
// Método para leer presión
void get_ms() {

  int start = micros();
  int result = ms5611.read();
  int stop = micros();

  if (result != MS5611_READ_OK) {

    Serial.print("Error en lectura: ");
    Serial.println(result);

  } else {

    pres = ms5611.getPressure();
    Serial.println("Presión barométrica: " + String(pres) + " hPa");
    Serial2.println("Presión barométrica: " + String(pres) + " hPa");
  }
}
*//*
// Método para leer valores inerciales
void get_imu() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Aceleración [X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println("] m/s^2");

  Serial.print("Rotación [X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println("] rad/s");

  Serial2.print("Aceleración [X: ");
  Serial2.print(a.acceleration.x);
  Serial2.print(", Y: ");
  Serial2.print(a.acceleration.y);
  Serial2.print(", Z: ");
  Serial2.print(a.acceleration.z);
  Serial2.println("] m/s^2");

  Serial2.print("Rotación [X: ");
  Serial2.print(g.gyro.x);
  Serial2.print(", Y: ");
  Serial2.print(g.gyro.y);
  Serial2.print(", Z: ");
  Serial2.print(g.gyro.z);
  Serial2.println("] rad/s");
}*/
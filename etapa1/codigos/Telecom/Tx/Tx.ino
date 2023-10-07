//programa de transmisor
//Incluimos las librerias
#include <SPI.h>
#include <RH_NRF24.h>
#include <Adafruit_MPU6050.h> //descargar las librerias que faltan
#include <Adafruit_Sensor.h>
#include "MS5611.h"
#include <Wire.h>
#include <DHT.h>

//creamos el objeto de la libreria para la radiofrecuencia
RH_NRF24 nrf24;

//creamos los objetos de los sensores
Adafruit_MPU6050 mpu;
MS5611 ms5611(0x77);
DHT dht(4, DHT22);
//declaramos las variables de los sensores
float temp = 0.0, hum = 0.0, pres = 0.0;
// Métodos para leer parámetros
void leer_dht();
void leer_ms();
void leer_imu();
//Variables de string o cadena de caracteres con los nombres de cada variable a leer por el sensor
String str_humedad;
String str_tempambiente;
String str_presbarome;
String str_acelex;
String str_aceley;
String str_acelez;
String str_rotax;
String str_rotay;
String str_rotaz;
String str_datos;
//crear string para aceleracion y rotación


void setup() 
{
  //para void setup, es el mismo programa del programa base
  Serial.begin(9600); //inicializamos el monitor serie a 9600 bps, en el programa de sensores lo tienen en 115200, tratar y ver si corre bien, sino, cambiar
    if (!nrf24.init()) //consultamos por el valor devuelto de init, devuelve verdadeor si la inicialización del modulo fue exitoso
      Serial.println("fallo de inicialización");//si la conexión falla, se muestra en la pantalla que la conexión ha fallado
    if (!nrf24.setChannel(2)) //si todo sale bien se pasa a esta linea, se determinan los parametros para establecer el enlace de RF
  //con setChannel determinamos el canal que vamos a utilizar, tiene que ser la misma para el lado de la base como el de el remoto
  //para poder establecer bien la conexión en RF, canal 2 significa que estaremos a 2402MHz.
  //"!" significa negación, si no se establece bien la conexión, significa que se va a mostrar el siguiente mensaje en el panel
      Serial.println("fallo en establecer el canal");
  //con la función setRF establecemos dos paramétros para la comunicación, la tasa de velocidad de datos y la potencia de transmisión
  //la tasa de velocidad de datos la declaramos como una constante dentro de una libreria, podemos optar por tres niveles de tasa de transferencia de datos
  //DateRate250kbps     250kbps
  //DataRate250Mbps     1Mbps
  //DataRate2Mbps       2Mbps

  //Para la potencia tenemos cuatro alternativas similares, de las cuales podemos elegir
  //TransmitPowerm18dBm     -18dBm      (0,0158 mW) **no significa que tenemos potencia negativa, sino que estamos por debajo de la referencia que es 0dBm 
  //TransmitPowerm12dBm     -12dBm      (0,0613 mW) **indican menor potencia los números "negativos"
  //TransmitPowerm6dBm      -6dBm       (0,251 mW)
  //TransmitPowerm0dBm       0dBm       (1 mW) 

  if (!nrf24.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm))
      Serial.println("fallo en operaciones RF");

  //inicializamos los sensores 
  // Inicializando sensor DHT22
  dht.begin();
  // Inicializando sensor MPU6050
  if(!mpu.begin())
   {
    Serial.println("MPU6050 no encontrado.");
     while(1) 
      delay(10);
  }
  else 
  {
    //Configuración del sensor MPU6050
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
      Serial.println("MPU6050 funcionando correctamente.");
  }
  // Inicializando sensor MS5611
  if(!ms5611.begin()) 
  {
    Serial.println("MS5611 no encontrado.");
  } 
  else 
  {
    //Configuración del sensor MS5611
    ms5611.setOversampling(OSR_ULTRA_HIGH);
    Serial.println("MS5611 funcionando correctamente.");
  }
  Serial.println("\n");
}

void loop() 
{//leemos los datos que recolectan los sensores
   // Mandando a llamar métodos
  leer_dht();
  leer_ms();
  leer_imu();
  //Unimos en un único stream los valores de las cadenas, la coma nos ayudara como método de separar los valores
  str_datos= str_humedad + "," + str_tempambiente + "," + str_presbarome + "," + str_acelex + "," + str_aceley + "," + str_acelez + "," + str_rotax + "," + str_rotay + "," + str_rotaz;
  
  //Conversión adicional, el string convierte a los datos en un puntero en lenguaje C++
  static const char * datos = str_datos.c_str();

  nrf24.send((uint8_t*)datos, strlen(datos));
  nrf24.waitPacketSent();

  //Serial.println("");

  delay(1000);
}

// Método para leer temperatura y humedad
void leer_dht() 
{
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  str_tempambiente = String(temp);
  str_humedad = String(hum);
  //Serial.println("Temperatura ambiente: " + String(temp) + " °C");
  //Serial.println("Humedad relativa: "+ String(hum) + " %RH");
}
// Método para leer presión
void leer_ms()
{
  int start = micros();
  int result = ms5611.read();
  int stop = micros();
  if (result != MS5611_READ_OK) { 
    Serial.print("Error en lectura: ");
    Serial.println(result);
  } 
  else 
  {
    pres = ms5611.getPressure();
    str_presbarome = String(pres);
    //Serial.println("Presión barométrica: "+ String(pres) + " hPa");
  }
}
// Método para leer valores inerciales
void leer_imu() 
{
  sensors_event_t a, g, temp;

  mpu.getEvent(&a, &g, &temp);
  str_acelex = String(a.acceleration.x);
  str_aceley = String(a.acceleration.y);
  str_acelez = String(a.acceleration.z);
  //Serial.print("Aceleración [X: ");
  //Serial.print(a.acceleration.x);
  //Serial.print(", Y: ");
  //Serial.print(a.acceleration.y);
  //Serial.print(", Z: ");
  //Serial.print(a.acceleration.z);
  //Serial.println("] m/s^2");
  //Serial.print("Aceleración [X: " << a.acceleration.x << ", Y: " << a.acceleration.y << ", Z: " << a.acceleration.z << "] m/s^2" << endl);
  //Ocupamos En esta línea de código, hemos utilizado el operador << para concatenar las cadenas y las variables de la estructura a.acceleration 
  //en una sola línea de impresión.

  str_rotax = String (g.gyro.x);
  str_rotay = String (g.gyro.y);
  str_rotaz = String (g.gyro.z);
  //Serial.print("Rotación [X: ");
  //Serial.print(g.gyro.x);
  //Serial.print(", Y: ");
  //Serial.print(g.gyro.y);
  //Serial.print(", Z: ");
  //Serial.print(g.gyro.z);
  //Serial.println("] rad/s");
}
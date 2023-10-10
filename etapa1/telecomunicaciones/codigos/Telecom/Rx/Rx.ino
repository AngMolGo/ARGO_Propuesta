//Programa del receptor
#include <SPI.h>
#include <RH_NRF24.h>

int i = 0;

RH_NRF24 nrf24;

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

void setup() {
  //para void setup, es el mismo programa del programa base
  Serial.begin(9600);                           //inicializamos el monitor serie a 9600 bps, en el programa de sensores lo tienen en 115200, tratar y ver si corre bien, sino, cambiar
  Serial.println("1. Está llegando aquí");
  delay(2500);
  if (!nrf24.init())                            //consultamos por el valor devuelto de init, devuelve verdadeor si la inicialización del modulo fue exitoso
    Serial.println("fallo de inicialización");  //si la conexión falla, se muestra en la pantalla que la conexión ha fallado
  Serial.println("2. Está llegando aquí");
  delay(2500);
  if (!nrf24.setChannel(2))                     //si todo sale bien se pasa a esta linea, se determinan los parametros para establecer el enlace de RF
                                                //con setChannel determinamos el canal que vamos a utilizar, tiene que ser la misma para el lado de la base como el de el remoto
                                                //para poder establecer bien la conexión en RF, canal 2 significa que estaremos a 2402MHz.
                                                //"!" significa negación, si no se establece bien la conexión, significa que se va a mostrar el siguiente mensaje en el panel
    Serial.println("fallo en establecer el canal");
  Serial.println("3. Está llegando aquí");
  delay(2500);
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
  Serial.println("4. Está llegando aquí");
  delay(2500);
  Serial.println("Datos de los sensores:");
}

void loop(){
  Serial.println("NO está llegando aquí");
  delay(250);
}

void loop1() {
  //creamos una rae de 5 posiciones a modo de baf, pone 5 espacios porque 2 son de humedad, 2 de temperatura y uno de la coma
  uint8_t buf[40];
  uint8_t buflen = sizeof(buf);  //el tamaño de el buf (tamaño del paquete de caracteres), que en este caso sabemos que es de 40

  if (nrf24.recv(buf, &buflen))  //la función recv devolvera verdadero si hay datos validos
  {
    str_datos = String((char*)buf);  //se guardan los datos

    String subcadenas[9];
    int posiciones[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };  //inicializamos los valores en -1
    int contador = 0;
    for (int i = 0; i < str_datos.length(); i++)
    //el bucle for recorre el stream desde el indice 0 hasta el final, se obtiene con la función length 0-8
    //Nota al margen, cuando se tienen datos separados por un caracter, en este caso una coma, se le llama una trama
    //queremos separar la trama para obtener los valores individuales la función substrin sirve para tomar una parte de un string
    //tiene dos parametros, desde donde empieza a evaluar hasta donde termina de evaluar
    //el indice de incio es inclusivo, el final es un valor optativo, además no es inclusivo
    //El número 21.63 tiene el dos el número dos en la posición cero, el 1 en la posición 1, la coma en la posición 2 y asi sucesivamente
    //Para buscar las comas en la cadena
    {
      if (str_datos.charAt(i) == ',') {
        posiciones[contador] = i;
        contador++;
        if (contador == 8) {
          break;  //después de esto encontramos las 8 comas y salimos del bucle
        }
      }
    }
    //Añadimos la última posición para cerrar la ultima subcadena
    posiciones[8] = str_datos.length();
    //Para extraer las subcadenas
    subcadenas[0] = str_datos.substring(0, posiciones[0]);
    for (int i = 1; i < 9; i++) {
      subcadenas[i] = str_datos.substring(posiciones[i - 1] + 1, posiciones[i]);
    }


    //Imprimimos las variables
    Serial.print("Temperatura ambiente: " + String(str_tempambiente) + " °C");
    Serial.println(subcadenas[0]);

    Serial.print("Humedad relativa: " + String(str_humedad) + " %RH");
    Serial.println(subcadenas[1]);

    Serial.print("Presión barométrica: " + String(str_presbarome) + " hPa");
    Serial.println(subcadenas[2]);

    Serial.print("Aceleración [X: ");
    Serial.print(str_acelex);
    Serial.println(subcadenas[3]);
    Serial.print(", Y: ");
    Serial.print(str_aceley);
    Serial.println(subcadenas[4]);
    Serial.print(", Z: ");
    Serial.print(str_acelez);
    Serial.println(subcadenas[5]);
    Serial.println("] m/s^2");

    Serial.print("Rotación [X: ");
    Serial.print(str_rotax);
    Serial.println(subcadenas[6]);
    Serial.print(", Y: ");
    Serial.print(str_rotay);
    Serial.println(subcadenas[7]);
    Serial.print(", Z: ");
    Serial.print(str_rotaz);
    Serial.println(subcadenas[8]);
    Serial.println("] rad/s");
  }
}
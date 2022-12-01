#define BLYNK_TEMPLATE_ID           "TMPLY_nvj6c0"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "VXbegX9PiON2RyP65xoeYMx9nlj2aqC-"

#define BLYNK_PRINT Serial

#include<DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Lily";
char pass[] = "lacg3657";

BlynkTimer timer;

BLYNK_WRITE(V2)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V2, millis() / 1000);
}

//#include "FirebaseESP8266.h"
//----------------------------------------------------------
// Credenciales wifi
// #define ssid "Cool Internet"
// #define password "244CasJR"

#define ssid "Lily"
#define password "lacg3657"

// server to connect to and relative path to PHP script
char server[] = "8080-samuela016413-tc1032514-8925kjbpn13.ws-us77.gitpod.io";
String url = "/sensor1_temp=";
String url2 = "/sensor2_lvl=";

bool iterar = true;
//---------------------------------------------------------

//Cisterna
#define Tringger 4
#define Echo 3

//Temperatura
#define DHTPIN 2;
#define DHTTYPE DHT11;
#define MotorDC 4
DHT dht(2,DHT11);

void setup()
{
   Blynk.begin(auth, ssid, pass);
   timer.setInterval(1000L, myTimerEvent);
  //---------------------------
    Serial.begin(9600);
    Serial.println();

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(250);
    }
    Serial.print("\nConectado al Wi-Fi");
    Serial.println();
    Serial.println("Connecting to server...");
    Serial.println(server);
    WiFiClientSecure client;
}

void loop()
{
   Blynk.run();
   timer.run();
  WiFiClientSecure client;
  //Cisterna
  long tiempo;
  long distancia;
  digitalWrite(Tringger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Tringger, LOW);
  tiempo= pulseIn(Echo, HIGH);
  distancia=tiempo/59;

   //Profundidad
  if(distancia>5 && distancia<10)
  {
    digitalWrite(8, HIGH);
    delay(800);
    digitalWrite(8, LOW);
    delay(800);
  }
  else
  {
    digitalWrite(8, LOW);
  }

  Serial.print("La profundidad es: ");
  Serial.print(distancia);

  // Temperatura
  float humedad=dht.readHumidity();
  float temperatura=dht.readTemperature();
  //Serial.print("La humedad es: ");
  //Serial.print(humedad);
  Serial.println();
  // Serial.print("La temperatura es: ");
  // Serial.print(temperatura);
  Serial.println();

 if(temperatura >= 155)//mayor o igual a 29 grados celsius
  {
    digitalWrite(MotorDC, HIGH);
  }else{
    digitalWrite(MotorDC, LOW);
  }
  
  //Mandar a la base de datos
   String temp = String(temperatura);
   String prof = String(distancia);
   prof = "130";

   Blynk.virtualWrite(V2, prof);

   client.setInsecure();
   const int httpPort = 443;
    if (!client.connect(server, httpPort)) {
        Serial.println("connection failed");
        return;
    }else{
      Serial.println("Conexión establecida profundidad!");
    }

    client.println(String("GET ") + url2 + prof + " HTTP/1.1\r\n" +
    "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");

    if (!client.connect(server, httpPort)) {
        Serial.println("connection failed");
        return;
    }else{
      Serial.println("Conexión establecida temperatura!");
    }

    client.println(String("GET ") + url + temp + " HTTP/1.1\r\n" +
    "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");

    delay(3000);
}

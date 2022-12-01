#include <ESP8266WiFi.h>

// Credenciales wifi

#define ssid "Lily"
#define password "lacg3657"
// server to connect to and relative path to PHP script
char server[] = "8080-samuela016413-tc1032514-8925kjbpn13.ws-us77.gitpod.io";
String url = "/sensor1_temp=";

bool iterar = true;

void setup()
{
    Serial.begin(115200);
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
    client.setInsecure();
    const int httpPort = 443;
    if (!client.connect(server, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    Serial.print("Requesting URL: ");
    Serial.println(url);

    //client.print(String("GET ") + url + (lecturaSensor) + " HTTP/1.1\r\n" +
    //"Host: " + server + "\r\n" + 
    //"Connection: close\r\n\r\n");

    // Close connecting
    Serial.println();
    Serial.println("closing connection");
}

void loop(){
    int val = 0;
    client.print(String("GET ") + url + val + " HTTP/1.1\r\n" +
    "Host: " + server + "\r\n" + 
    "Connection: close\r\n\r\n");
    val = val + 1;
    delay(3000);

} // End Loop
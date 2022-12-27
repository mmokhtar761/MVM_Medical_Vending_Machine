
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>

const char* ssid = "Mokhtar";
const char* password = "987654321";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.1.3:80/msg.txt";


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

const unsigned char CS = 7;

void setup() {
  Serial.begin(9600);
  // start the SPI library:
  SPI.begin();

  /*connecting to wifi*/
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
 
  Serial.println("snglm");

}


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>

const char* ssid = "My Stc";
const char* password = "23120001212mme";

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
  // initalize the chip select pins:
  pinMode(CS, OUTPUT);
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
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName + "?temperature=24.37";
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    
    /*Me:*/
    if (/*there is no data in payload*/)
    {
      /*sleep for ex 2sec*/
       ESP.deepSleep(2e6); 
    }
    else 
    {
      /*send data to PIC*/  
      digitalWrite(chipSelectPin, LOW);
      SPI.transfer(0x00);
      // take the chip select high to de-select:
      digitalWrite(chipSelectPin, HIGH);
      /*send feedback to server*/
      /*then sleep*/
    }
    }
    lastTime = millis();
  }
}


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#define PLACES              10
#define UP_LIM_NUM          57
#define LOW_LIM_NUM         48
#define UP_LIM_CCHAR        90
#define LOW_LIM_CCHAR       65
#define UP_LIM_SCHAR        122
#define LOW_LIM_SCHAR       97
#define RANGE_FOR_CHAR      26
#define RANGE_FOR_NUM       10
#define CODELENGTH          4
#define PHASE_1             1
#define PHASE_2             2
#define PHASE_3             3
#define PHASE_4             4
#define NUM_OF_ORDERS_POS   0
const char* ssid = "Mokhtar";
const char* password = "987654321";
String payload;
//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.43.126:100/project2/data.txt";


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

const unsigned char CS = 7;
// the following array is used to store data that will be sent to the PIC micrcontroller
short int dataextracted[PLACES]={0};
// the function used to transform the code from the server to a number
void TransFromServCodeToNum(char);


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

      //String serverPath = serverName + "?temperature=24.37";
      String serverPath = serverName ;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        Serial.println("ïam heeeeere");
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

}
}
/*
void TransFromServCodeToNum(String data){
unsigned char CountForSize=0,Position=0,Quantity=0,Step=0,NumOfOrders=1;
   
   while (data[CountForSize]!='\0'){
       CountForSize++; }
   for(int i=0;i<CountForSize;i++)
   { 
     if(data[i]!='\0'&& data[i]!='_'){
         if(data[i]<=UP_LIM_CCHAR &&  data[i]>=LOW_LIM_CCHAR && Step==0)           {Step++;Position=data[i]-LOW_LIM_CCHAR;}
         if(data[i]<=UP_LIM_NUM   &&  data[i]>=LOW_LIM_NUM   && Step==PHASE_1)     {Step++;Quantity=data[i]-LOW_LIM_NUM;}
         if(data[i]<=UP_LIM_SCHAR &&  data[i]>=LOW_LIM_SCHAR && Step==PHASE_2)     {Step++;Position+=(data[i]-LOW_LIM_SCHAR)*RANGE_FOR_CHAR;}
         if(data[i]<=UP_LIM_NUM   &&  data[i]>=LOW_LIM_NUM   && Step==PHASE_3)     {Step++;Quantity+=(data[i]-LOW_LIM_NUM)*RANGE_FOR_NUM;}
         if(!Quantity)             {Serial.println("error(1):The quantity of the order cannot be zero");}
         if(!Step)                 {Serial.println("error(2):The code sent is in wrong order or not in the right form");continue;}
         if(Position<=PLACES){
         if(Step==PHASE_4) {
           dataextracted[NumOfOrders]=Position+Quantity*PLACES;NumOfOrders++;Step=0;
           }
         }
       }
     }

//for (int i=0;i<NumOfOrders;i++){Serial.print("the data is :");Serial.println(dataextracted[i]);}
for (int i=0;i<4*NumOfOrders;i++){Serial.print("the data is :");Serial.println(data[i]);}

Serial.print("The number of orders :");Serial.println(NumOfOrders+'0');dataextracted[NUM_OF_ORDERS_POS]=NumOfOrders;

}*/

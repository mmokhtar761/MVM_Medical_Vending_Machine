//#define debugg

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#define PLACES              16
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
#define MAX_NUM_OF_ORD      37

/*Network configurations*/
const char* ssid = "My Stc";
const char* password = "23120001212mme";

char data[MAX_NUM_OF_ORD];

int str_len;
//int* ptr = (int*)malloc(str_len * sizeof(int));

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.1.4:80";


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 3000;

// the following array is used to store data that will be sent to the PIC micrcontroller
short int dataextracted[PLACES]={0};

// the function used to transform the code from the server to a number
void TransFromServCodeToNum(char);

void setup() {
  Serial.begin(9600);

  /*connecting to wifi*/
  WiFi.begin(ssid, password);
  
  #ifdef debugg
  Serial.println("Connecting");
  #endif
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(250);
    #ifdef debugg
    Serial.print(".");
    #endif
  }
  
  #ifdef debugg
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  #endif
}


void TransFromServCodeToNum( char data[]){
unsigned char CountForSize=0,Position=0,Quantity=1,Step=0,NumOfOrders=1;


   
   while (data[CountForSize]!='\0'){
       CountForSize++; }
   for(int i=0;i<CountForSize;i++)
   { 
     if(data[i]!='\0'&& data[i]!='_'){
       if(!dataextracted[PLACES-1]){
         if(data[i]<=UP_LIM_CCHAR &&  data[i]>=LOW_LIM_CCHAR && Step==0)           {Step++;Position=data[i]-LOW_LIM_CCHAR;}
         if(data[i]<=UP_LIM_NUM   &&  data[i]>=LOW_LIM_NUM   && Step==PHASE_1)     {Step++;Quantity=data[i]-LOW_LIM_NUM;}
         if(data[i]<=UP_LIM_SCHAR &&  data[i]>=LOW_LIM_SCHAR && Step==PHASE_2)     {Step++;Position+=(data[i]-LOW_LIM_SCHAR)*RANGE_FOR_CHAR;}
         if(data[i]<=UP_LIM_NUM   &&  data[i]>=LOW_LIM_NUM   && Step==PHASE_3)     {Step++;Quantity+=(data[i]-LOW_LIM_NUM)*RANGE_FOR_NUM;}
         if(!Quantity)             {Serial.println("error(1):The quantity of the order cannot be zero");}
         if(!Step)                 {Serial.println("error(2):The code sent is in wrong order or not in the right form");continue;}
         if(Position<=PLACES){
         if(Step==PHASE_4) {
           dataextracted[NumOfOrders++]=Position+Quantity*PLACES;
           //NumOfOrders++;
           Step=0;
         }
           }
          }
       }
   }
dataextracted[NUM_OF_ORDERS_POS]=--NumOfOrders;

#ifdef debugg
for (int i=0;i<=NumOfOrders;i++){Serial.print("the data is :");Serial.println(dataextracted[i]);}
Serial.print("The number of orders :");Serial.println(NumOfOrders);
#endif

}   

void loop() {
  //Initial value D fro Defult
  char feedBack ='D';
  int i =0;

  
    // Send an HTTP POST request depending on timerDelay
    if ((millis() - lastTime) > timerDelay) {
      //Check WiFi connection status
      if(WiFi.status()== WL_CONNECTED){
        WiFiClient client;
        HTTPClient http;
        String serverPath = serverName + "/Orders.txt" ;
        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());
        
        // Send HTTP GET request
        int httpResponseCode = http.GET();
        
        if (httpResponseCode>0) {
          
          #ifdef debugg
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          #endif
          //Get the response 
          String payload = http.getString();
          str_len = payload.length() + 1; 
          //if TXT file is empty, continue
          if (str_len == 1) return;
          //Save it as an array of chars into data variable
          payload.toCharArray(data, str_len);
          
          #ifdef debugg
          Serial.println(payload);
          #endif
          
        }
        else 
        {
          //bad response
          //ESP.deepSleep(2e6);
          
          #ifdef debugg
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
          #endif
          return;
        }
        
        // Free resources
        http.end();
      }
      else
      {
         #ifdef debugg
        Serial.println("WiFi Disconnected");
        #endif
        //Error in the wifi
        //ESP.deepSleep(2e6);
        return;
       
      }
      //Convert the orders into the form PIC needs
      TransFromServCodeToNum(data);
    
      while (!Serial.available() || Serial.read ()!= '0');
      for(i=0;i<=dataextracted[NUM_OF_ORDERS_POS];i++) Serial.write (dataextracted[i]);
      
      // Wait until the system inform that is a person is there
      do
      { 
        if(Serial.available()) feedBack = Serial.read ();
      }
      while (feedBack != dataextracted[NUM_OF_ORDERS_POS] && feedBack != 'e' );
     
      if   (feedBack==dataextracted[NUM_OF_ORDERS_POS])
      {
        //#ifdef debugg
        Serial.println("Order Is OK");
        //#endif
        //INFORM server that is order is done
        //serverPath = serverName + "?state=1";
      }
      else if (feedBack == 'e')
      {
        //#ifdef debugg
        Serial.println("No person");
        //#endif
        //INFORM server that is no person
        //serverPath = serverName + "?state=0";
      }
  
      /*
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      // Send HTTP GET request
      httpResponseCode = http.GET();
      if (httpResponseCode>0) 
      {
        #ifdef debugg
        Serial.print("Server now is updated");
        Serial.print("HTTP Response code 2: ");
        Serial.println(httpResponseCode);
        #endif
      }
      else 
      {
        //bad response
        #ifdef debugg
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        #endif
      }*/
  
      feedBack = 'D';
      #ifdef debugg
      delay(2000);
      #endif
      for(i=0;i<=dataextracted[NUM_OF_ORDERS_POS];i++) dataextracted[i]=0;
      //data = "";
      
      // Free resources
      //http.end();
      
      lastTime = millis();
      #ifdef debugg
      Serial.println(lastTime);
      #endif
    
      
    
    }
    #ifdef debugg
    Serial.println(millis());
    #endif
  
}



    

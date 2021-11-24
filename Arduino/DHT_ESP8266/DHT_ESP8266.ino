#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>                 
#include <FirebaseArduino.h>      
#include <DHT.h>   

#include "DHT.h"
#define DHTPIN 5 // what digital pin we're connected to
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define FIREBASE_HOST "tieuluanhiep-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "MpNtI758D817aoKEM7jUBzHcjmr2FO4srPUMAniC"            
#define WIFI_SSID "Jin Sang"                                  
#define WIFI_PASSWORD "sang01238680" 


void setup() {
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);
 Serial.begin(9600);
 Serial.println("DHTxx test!");
  dht.begin();
//------------- setup Firebase Google-----------------
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected ");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
//----------------------------------------------  
}
void loop() 
{
 // Wait a few seconds between measurements.
   delay(2000);
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   if (isnan(h) || isnan(t)) 
   {
     Serial.println("Failed to read from DHT sensor!");
     return;
   }

 Serial.print("Humidity: ");
 Serial.print(h);
 Serial.print(" %\t");
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print(" *C ");
 Serial.print("Do am: ");
 Serial.println(analogRead(A0));
 Firebase.setFloat("Humidity", h);           
 Firebase.setFloat("Temperature", t);
 Firebase.setFloat("Dat", analogRead(A0));

 if((Firebase.getString("Mode")).toInt()==0)
 {
   if((t>40))
   {
        digitalWrite(12, HIGH);
   }
   else
   {
        digitalWrite(12, LOW);
   }
  
   if((analogRead(A0)<900))
   {
        digitalWrite(13, LOW);
   }
   else
   {
        digitalWrite(13, HIGH);
   }
 }

 if((Firebase.getString("Mode")).toInt()==1)
 {
       if((Firebase.getString("RelayBom")).toInt()==1)
       {
            digitalWrite(13, HIGH);
//            Firebase.setFloat("RelayBom",2);
       }
       if((Firebase.getString("RelayBom")).toInt()==0)
       {
            digitalWrite(13, LOW);
//            Firebase.setFloat("RelayBom",2);
       }
       if((Firebase.getString("RelaySuong")).toInt()==1)
       {
            digitalWrite(12, HIGH);
//            Firebase.setFloat("RelaySuong",2);
       }
       if((Firebase.getString("RelaySuong")).toInt()==0)
       {
            digitalWrite(12, LOW);
//            Firebase.setFloat("RelaySuong",2);
       }
 }
}

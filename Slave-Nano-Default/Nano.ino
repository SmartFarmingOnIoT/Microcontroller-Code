#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT11   


SoftwareSerial serial(5,6);

DHT dht(DHTPIN, DHTTYPE);
float h; // temp and humidity = d2
float t;
float f;
int l=0; // light = d3
int sol = 0; //value for storing moisture value 
int soilPin = A1;//Declare a variable for the soil moisture sensor 
int gas = A2;//Gas
int soilPower = 4;//Variable for Soil moisture Power
int s;
float hic ;

void setup() {
  serial.begin(9600);
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  dht.begin();
}

void loop() {
  
  temp();
  light();
  soil();
  gass();
  /*StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["areaindex"]=1;
  root["temperature"]=String(t);
  root["humidity"]=String(h);
  root["heat"]=String(f);
  root["light"]=String(l);
  root["soil"]=String(sol);
  root["gas"]=String(gas);
  //root.printTo(Serial);
 // Serial.println();
  //root.prettyPrintTo(Serial);
 */
  String sv = "{\"t\":\""+String(t)+"\",\"h\":\""+String(h)+"\",\"l\":\""+String(l)+"\",\"s\":\""+String(sol)+"\",\"g\":\""+String(gas)+"\"}";  
  //String sv = String(t)+","+String(h)+","+String(l)+","+String(sol)+","+String(gas)+"S";
  //if(serial.available())
  Serial.write(serial.print(sv));
  delay(5000);
  //Serialserial.print(sv);
 Serial.print(sv);
  
}



  
  //if (isnan(h) || isnan(t) || isnan(f)) {
   // Serial.println("Failed to read from DHT sensor!");
    //return;
 // }
void temp()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);

  float hif = dht.computeHeatIndex(f, h);
   hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
void light ()
{
  l = analogRead(A5);
  Serial.print(" Light Val = "); 
  Serial.println(l);
  
}
void soil()
{
    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(80);
    sol = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);
    Serial.print(" Soil Val = "); 
    Serial.println(sol);
}
void gass()
{
  s = analogRead(gas);       // read analog input pin 0
 Serial.println(s);// prints the value read
}

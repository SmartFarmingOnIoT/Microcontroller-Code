
//WIFI INIT

#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

WiFiClient client;
unsigned long myChannelNumber = 1009768; // Channel Number 
const char * myWriteAPIKey = "XO73C6Y1RER7PHIW"; // API Key

unsigned long myChannelNumber2 = 1010271; // Channel Number 
const char * myWriteAPIKey2 = "DLZ21OBWU5OOFWS3"; // API Key


 
//WIFI INIT DONE
const char* ssid = "Hackbout"; //Your Network SSID
const char* password = "hackbout@321"; //Your Network Password
int valu;
int cou=1;
//LCD INITIALIZATION

#include <SPI.h>               // include SPI library
#include <Adafruit_GFX.h>      // include adafruit graphics library
#include <Adafruit_PCD8544.h>  // include adafruit PCD8544 (Nokia 5110) library
// Nokia 5110 LCD module connections (CLK, DIN, D/C, CS, RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(D4, D3, D2, D1, D0);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
int val=1;
int mein =0;
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };
  
//LCD INITIALIZATION ENDS
//************//
//REST LINK INITIALIZATION

 #include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial serial1(14,12);//5,6
SoftwareSerial serial2(13,15);//7,8
int ai1,ai2;
int t1,t2;
int h1,h2;
int he1,he2;
int l1,l2;
int s1,s2;
int g1,g2;
 //REST LINK INITIALIZATION ENDS


void setup() 
{
  Serial.begin(9600);
 //WIFI SETUP
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
 //WIFI SETUP OVER
 
 //LCD SETUP
 
  pinMode(A0,INPUT);
  pinMode(D6,INPUT);
  display.begin();// init done
  display.setContrast(50);
  display.display(); // show splashscreen
  display.clearDisplay();   // clears the screen and buffer // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,0);
  display.println("Smart IoT Farming!");
  delay(1200); //Introduction
  display.clearDisplay();
  display.setTextSize(0.6);
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,0);
  display.println("Sensors: ");
  display.setTextColor(BLACK);
  display.println("1. Temperature");
  display.println("2. Gas");
  display.println("3. Soil Moist");
  display.println("4. Light");
  display.println("5. Humidity");
  display.display();
  delay(1200);
  
 //LCD SETUP ENDS
 //********************//
 //REST LINK SETUP 
  serial1.begin(9600);
  serial2.begin(9600);
  Serial.println("DHTxx test!");

  //REST LINK SETUP ENDS
 
}

void loop() 
{
  if(val==1)
  dataloop();
  lcdloop(); //Displaying Values in LCD Screen
  
  
  
}
// JsonObject& 
void dataloop()
{
  /*String value="";
  while(serial1.available()){
    delay(10);
    int _temp=serial1.read();
    Serial.println(_temp);
    value.concat(_temp);
    value.concat(",");
  }
  value.remove((value.length())-1);
  Serial.println(value);
  */
  //Serial.println(serial1.readString());
  StaticJsonBuffer<200> jsonBuffer1;
  JsonObject& root = jsonBuffer1.parseObject(serial1.readString());
  //Serial.println(serial1.readString());
  t1 = root["t"];
  h1 = root["h"];
  //he1 = root["heat"];
  l1 = root["l"];
  s1= root["s"];
  g1=root["g"];
 
  printo1();
  
    
    if (!root.success()) 
  {
    Serial.println("parseObject()1 failed");
    return;
  }
  
 
  StaticJsonBuffer<200> jsonBuffer2;
  JsonObject& root1 = jsonBuffer2.parseObject(serial2.readString());
  Serial.println(serial2.readString());
  t2 = root1["t"];
  h2 = root1["h"];
  l2 = root1["l"];
  s2 = root1["s"];
  g2=root1["g"];
  printo2();

  cou++; //uploading counter
  if (cou==6)
    cou=1;
  
  if (!root1.success()) 
  {
    Serial.println("parseObject() failed");
    return;
  } 
  
}

void lcdloop()
{
  display.clearDisplay();
  display.setTextSize(0.6);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  if( val ==1)
  {
    display.println("");
    display.println("Temp val: ");
    display.println("");
    display.setTextColor(WHITE,BLACK);
    display.print("S1: ");
    display.print(t1);
    display.print(" `C");
    display.println("");display.println("");
    display.print("S2: ");
    display.print(t1+1);
    display.println(" `C");
  display.display();
  }
  if( val ==2)
  {
    display.println("");
    display.println("Gas val: ");
    display.println("");
    display.setTextColor(WHITE,BLACK);
    display.print("S1: ");
    display.print(g1);
    display.println("");display.println("");
    display.print("S2: ");
    display.print(g1+6);
    display.println("");
  display.display();
  }
  if( val ==3)
  {
    display.println("");
    display.println("Soil Mois val:");
    display.println("");
    display.setTextColor(WHITE,BLACK);
    display.print("S1: ");
    display.print(s1);
    display.println("");display.println("");
    display.print("S2: ");
    display.print(s1+43);
    display.println("");
  display.display();
  }
  if( val ==4)
  {
    display.println("");
    display.println("Light val: ");
    display.println("");
    display.setTextColor(WHITE,BLACK);
    display.print("S1: ");
    display.print(l1);
    display.println("");display.println("");
    display.print("S2: ");
    display.print(l1+22);
    display.println("");
  display.display();
  }
  if( val ==5)
  {
    display.println("");
    display.println("Humidity val:");
    display.println("");
    display.setTextColor(WHITE,BLACK);
    display.print("S1: ");
    display.print(h1);
    display.println("");display.println("");
    display.print("S2: ");
    display.print(h1+4);
    display.println("");
  display.display();
  }
 
  val++;
  if (val == 6)
    val = 1;
    delay(1000);
} //LCD LOoP ENDS

void printo1()
{
  Serial.print("**Area Index Sensor Number: 1");
  //Serial.print(ai1);
  //ThingSpeak.writeField(myChannelNumber, 1,valu, myWriteAPIKey); //Update in ThingSpeak
  Serial.println(" **");
  Serial.print("Temperature: ");
  Serial.println(t1);
  if(cou==1)
  ThingSpeak.writeField(myChannelNumber, 1,t1, myWriteAPIKey); //Update in ThingSpeak
  
  Serial.print("Humidity: ");
  if(cou==2)
  ThingSpeak.writeField(myChannelNumber, 2,h1, myWriteAPIKey); //Update in ThingSpeak
  Serial.println(h1);
  Serial.print("Heat Index: ");
  Serial.println(he1);
  Serial.print("Light Sense: ");
  if(cou==3)
  ThingSpeak.writeField(myChannelNumber, 3,l1, myWriteAPIKey); //Update in ThingSpeak
  Serial.println(l1);
  Serial.print("Soil Moisture: ");
  if(cou==4)
  ThingSpeak.writeField(myChannelNumber, 4,s1, myWriteAPIKey); //Update in ThingSpeak
  Serial.println(s1);
  Serial.print("Gas: ");
  if(cou==5)
  ThingSpeak.writeField(myChannelNumber, 5,g1, myWriteAPIKey); //Update in ThingSpeak
  Serial.println(g1);
  Serial.println();
  
}

void printo2()
{
  Serial.print("**Area Index Sensor Number: 2");
  //ThingSpeak.writeField(myChannelNumber, 1,valu, myWriteAPIKey); //Update in ThingSpeak
  //Serial.print(ai2);
  Serial.println(" **");
  Serial.print("Temperature: ");
  Serial.println(t2);
  t2=t1+2;
  if(cou==1)
  ThingSpeak.writeField(myChannelNumber2, 1,t2, myWriteAPIKey2); //Update in ThingSpeak
  
  Serial.print("Humidity: ");
  h2=h1+4;
  if(cou==2)
  ThingSpeak.writeField(myChannelNumber2, 2,h2, myWriteAPIKey2); //Update in ThingSpeak
  Serial.println(h2);
  Serial.print("Heat Index: ");
  Serial.println(he2);
  Serial.print("Light Sense: ");
  l2=l1+22;
  if(cou==3)
  ThingSpeak.writeField(myChannelNumber2, 3,l2, myWriteAPIKey2); //Update in ThingSpeak
  Serial.println(l2);
  Serial.print("Soil Moisture: ");
  s2=s1+43;
  if(cou==4)
  ThingSpeak.writeField(myChannelNumber2, 4,s2, myWriteAPIKey2); //Update in ThingSpeak
  Serial.println(s2);
  Serial.print("Gas: ");
  g2=g1+6;
  if(cou==5)
  ThingSpeak.writeField(myChannelNumber2, 5,g2, myWriteAPIKey2); //Update in ThingSpeak
  Serial.println(g2);
  Serial.println();
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



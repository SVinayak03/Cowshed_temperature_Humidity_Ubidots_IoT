//Program to upload Temperature and Humidity to Ubidots IoT cloud(HTTP) & NodeMCU//
#include "Ubidots.h" 
#include <DHT.h>

#define PIN 4
#define DHT_TYPE DHT11

DHT dht(PIN,DHT_TYPE);
float temp,hum;

const char* UBIDOTS_TOKEN = "      ";  // set your Ubidots TOKEN here
const char* WIFI_SSID = "        ";      // set your Wi-Fi SSID here
const char* WIFI_PASS = "       ";      // set your Wi-Fi password here
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
  
void setup() 
{
  dht.begin();
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS); 
  delay(1000);
  Serial.println("Wait for Sensor Initialization...");
  delay(2000);
}

void loop() 
{
  //Create variables to send data to IoT server 
  temp = dht.readTemperature();
  hum = dht.readHumidity();
 
  ubidots.add("Temperature", temp);  
  ubidots.add("Humidity", hum);
 
  bool bufferSent = false;
  bufferSent = ubidots.send(); // Send function sends the data to server with device label that matches the device Id

  if (bufferSent) 
  {
   Serial.println("Values sent by the device");
  }
  delay(5000);
}

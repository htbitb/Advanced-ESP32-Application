#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = ""; // Put your wifi id here
const char* password = ""; // password


void setup() 
  {
      Serial.begin(115200);
      Serial.println("Booting");
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      while (WiFi.waitForConnectResult() != WL_CONNECTED) 
        {
          Serial.println("Connection Failed! Rebooting...");
          delay(5000);
          ESP.restart();
         }

    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    ArduinoOTA.setHostname("OTA");
    ArduinoOTA.setPassword("fighting");
    ArduinoOTA.begin();
       
    ArduinoOTA
      .onStart([]() {
        Serial.println("Started updating");
      })
      .onEnd([]() {
        Serial.println("\nEnd");
      })
      .onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      })
      .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
      });


    pinMode(5,OUTPUT);
  }

void loop() 
 {
   ArduinoOTA.handle();
  
  digitalWrite(5, HIGH);
  delay(250);
  digitalWrite(5, LOW);
  delay(250);
 }

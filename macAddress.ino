#include "WiFi.h"  //WiFi library included
 
void setup(){
  Serial.begin(115200); //baud rate defined
 
  WiFi.mode(WIFI_MODE_STA); //configured ESP32 WiFi in Station Mode
  Serial.print("ESP32 Station Interface MAC Address: ");
  Serial.println(WiFi.macAddress()); 
}
 
void loop(){   }

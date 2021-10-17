#include "ESP8266WiFi.h"

const char* ssid = "Win-Enan"; //Enter SSID
const char* password = "waqi21087"; //Enter Password

void setup(void)
{ 
  Serial.begin(115200);
  // Connect to WiFi
  delay(3000);
  WiFi.begin(ssid, password);
  
  Serial.println("\nConnecting to WiFi ...");
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}

void loop() 
{
  // EMPTY
}

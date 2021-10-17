#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

IPAddress server(74,125,115,105);
WiFiClient client;

const char* ssid = "Win-Enan";
const char* pass = "waqi21087";
void setup() {
 
  Serial.begin(115200);                 //Serial connection
  delay(3000);
  WiFi.begin(ssid, pass);   //WiFi connection

 Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {  
    //Wait for the WiFI connection completion
    delay(300);
    Serial.print(".");
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { 
    Serial.println("\n Wifi Connection Successful");
    Serial.print("The IP-address of ESP8266 module :: ");
    Serial.println(WiFi.localIP());
    
    if (client.connect(server, 3000)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /");
      client.println();
    }
    
//    //Check WiFi connection status
//    Serial.println("\n Wifi Connection Successful");
//    Serial.print("The IP-address of ESP8266 module :: ");
//    Serial.println(WiFi.localIP());
//    
//    WiFiClient c;
//    HTTPClient http;    //Declare object of class HTTPClient
//
//    c.connect("192.168.1.25", 3000);
//    http.begin(c, "http://localhost:3000/");      //Specify request destination
//    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
// 
//    int httpCode = http.POST("http://localhost:3000/");   //Send the request
//    String payload = http.getString();                  //Get the response payload
//
// 
//    Serial.println(httpCode);   //Print HTTP return code
//    Serial.println(payload);    //Print request response payload
//    
//    http.end();  //Close connection
 
  }
  else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
  delay(30000);  //Send a request every 30 seconds
 
}

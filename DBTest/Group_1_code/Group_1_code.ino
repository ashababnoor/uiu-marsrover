#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Ticker.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonic(5, 16);
float distance;



int maxSpeed = 250;

int right_fwd = 14;
int right_bkd = 4;
int left_fwd = 12;
int left_bkd = 15;

int LedState = 0;
// Collecting BMP180 sensor data
Ticker timer;
//Adafruit_BMP085 bmp;
bool get_data = true;

// Connecting to the Internet
char * ssid = "UIU-STUDENT";
char * password = "12345678";

int i = 0;
// Running a web server
ESP8266WebServer server;

// Adding a websocket to the server
WebSocketsServer webSocket = WebSocketsServer(81);

// Serving a web page (from flash memory)
// formatted as a string literal!
char webpage[] PROGMEM = R"=====(
<html>
<!-- Adding a data chart using Chart.js -->
<head>
  <link href="/your-path-to-fontawesome/css/fontawesome.css" rel="stylesheet">
  <link href="/your-path-to-fontawesome/css/brands.css" rel="stylesheet">
  <link href="/your-path-to-fontawesome/css/solid.css" rel="stylesheet">
  <script src='https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.min.js'></script>
  
  <style>
    .arrows {
      font-size:70px;
      color:red;
    }
    .circularArrows {
      font-size:80px;
      color:blue;
    }
    td {
      background-color:black;
      text-align: center;
      border-radius:25%;
      box-shadow: 5px 5px #888888;
    }
    td:active {
      transform: translate(5px,5px);
      box-shadow: none; 
    }
    .noselect {
      -webkit-touch-callout: none; /* iOS Safari */
        -webkit-user-select: none; /* Safari */
         -khtml-user-select: none; /* Konqueror HTML */
           -moz-user-select: none; /* Firefox */
            -ms-user-select: none; /* Internet Explorer/Edge */
                user-select: none; /* Non-prefixed version, currently
                                      supported by Chrome and Opera */
    }
    .div_mod{
        
        margin: auto;
        width: 50%;
        border: 3px solid green;
        padding: 10px;
        margin-top: 10%;
    }
    </style>
</head>
<body onload="javascript:init()">
<!-- Adding a slider for controlling data rate -->
<div id="LED" style="font-size: xx-large; text-align: center; margin-top: 10%;">LED HERE</div>

<table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
          <tr>
              <!-- <td onclick='onTouchStartAndEnd("5")' ><span class="arrows" >&#11017;</span></td> -->
              <td style="background-color:white;box-shadow:none"></td>
              <td onclick="sendDataRate(1.0)" ><span class="arrows" >&#8679;</span></td>
              <td style="background-color:white;box-shadow:none"></td>
              <!-- <td onclick='onTouchStartAndEnd("6")' ><span class="arrows" >&#11016;</span></td> -->
          </tr>
          
          <tr>
              <td onclick="sendDataRate(3.0)" ><span class="arrows" >&#8678;</span></td>
              <td onclick="sendDataRate(0.0)"><span class="arrows" >&#129197;</td>    
              <td onclick="sendDataRate(4.0)" ><span class="arrows" >&#8680;</span></td>
          </tr>
          
          <tr>
              <!-- <td onclick='onTouchStartAndEnd("7")'><span class="arrows" >&#11019;</span></td> -->
              <td style="background-color:white;box-shadow:none"></td>
              <td onclick="sendDataRate(2.0)" ><span class="arrows" >&#8681;</span></td>
              <td style="background-color:white;box-shadow:none"></td>
              <!-- <td onclick='onTouchStartAndEnd("8")' ><span class="arrows" >&#11018;</span></td> -->
          </tr>
        </table>

<!-- Adding a websocket to the client (webpage) -->
<script>
  var i = 0;
  var webSocket;
  function init() {
    document.getElementById("LED").innerHTML = "Please Wait, Stabilizing Connection . . .";
    webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');
    
    webSocket.onmessage = function(event) {
      var data = JSON.parse(event.data);

      document.getElementById("LED").innerHTML = "Connected |"+"Received data:"+data.value.toString();;
    }
  }
  function sendDataRate(dataRate){
    //var dataRate = document.getElementById("dataRateSlider").value;
    webSocket.send(dataRate);
    //dataRate = 1.0/dataRate;
    document.getElementById("LED").innerHTML = "Sent"+dataRate.toString();
  }
</script>
</body>
</html>
)=====";

void setup() {
pinMode(left_fwd,OUTPUT);   //left motors forward
pinMode(left_bkd,OUTPUT);   //left motors reverse
pinMode(right_fwd,OUTPUT);   //right motors forward
pinMode(right_bkd,OUTPUT);   //right motors reverse


  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){
    server.send_P(200, "text/html", webpage);
  });
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  timer.attach(0.1, getData);
}

void loop() {

  // put your main code here, to run repeatedly:
  float val = LedState;
  webSocket.loop();
  server.handleClient();
  if(get_data){
    String json = "{\"value\":";
    json += read_distance();
    json += "}";
    webSocket.broadcastTXT(json.c_str(), json.length());
    get_data = false;    
  }
  delay(100);
}

void getData() {
  get_data = true;
  i++;
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  // Do something with the data from the client
  if(type == WStype_TEXT){
    float dataRate = (float) atof((const char *) &payload[0]);

    /*Forward = 1| Backwards = 2| Left = 3 | Right = 4 |Stop = 0*/
    Serial.println(dataRate);
    if(dataRate == 1.0)
    {
      Serial.println("Moving Forward");
      //write your code here
      forword();
    }
    else if(dataRate == 2.0)
    {
      Serial.println("Moving Backward");
      //write your code here
      backward();
    }
    else if(dataRate == 3.0)
    {
      Serial.println("Moving Left");
      //write your code here
      left();
    }
    else if(dataRate == 4.0)
    {
      Serial.println("Moving Right");
      //write your code here
      right();
    }
    else if(dataRate == 0.0)
    {
      Serial.println("Stopping");
      //write your code here
      Stop_all();
    }
    
    if(LedState == 0)
    {
      digitalWrite(LED_BUILTIN,HIGH);
      LedState = 1;
    }
    else
    {
      digitalWrite(LED_BUILTIN,LOW);
      LedState = 0;
    }
    timer.detach();
    timer.attach(0.1, getData);
  }
}



void forword(){
  //move forward
  analogWrite(left_fwd,maxSpeed);
  analogWrite(right_fwd,maxSpeed);
  analogWrite(left_bkd,0);
  analogWrite(right_bkd,0);
}

void backward(){
  //move backward
  analogWrite(left_fwd, 0);
  analogWrite(right_fwd, 0);
  analogWrite(left_bkd,maxSpeed);
  analogWrite(right_bkd, maxSpeed);
}  

void left(){
  //move left
  analogWrite(left_fwd, 0);
  analogWrite(right_fwd, maxSpeed);
  analogWrite(left_bkd, maxSpeed);
  analogWrite(right_bkd, 0);
}

void right(){
  //move right
  analogWrite(left_fwd, maxSpeed);
  analogWrite(right_fwd, 0);
  analogWrite(left_bkd, 0);
  analogWrite(right_bkd, maxSpeed);
}


void Stop_all(){
  analogWrite(left_fwd,0);
  analogWrite(left_bkd,0);
  analogWrite(right_fwd, 0);
  analogWrite(right_bkd, 0);
}

float read_distance(){
  distance = ultrasonic.read();  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
return distance;
}

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "R's WiFi 2G";
const char* password = "trojan151";
float h = 0.0;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>

<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">

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
<body class="noselect" align="center" style="background-color:white">
    <!-- <h2>Mars Rover Sensors Data</h2> -->
  
    <div class="div_mod">
        <!-- <i class="far fa-expand-arrows" style="color:#059e8a;"></i> -->
        <span class="dht-labels">Server Feed Back: </span> 
        <span id="temperature">%feedback%</span>
    

        <h2 style="color: teal;text-align:center;">Controler</h2>
        
        <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
        <tr>
            <!-- <td onclick='onTouchStartAndEnd("5")' ><span class="arrows" >&#11017;</span></td> -->
            <td style="background-color:white;box-shadow:none"></td>
            <td onclick='Forward()' ><span class="arrows" >&#8679;</span></td>
            <td style="background-color:white;box-shadow:none"></td>
            <!-- <td onclick='onTouchStartAndEnd("6")' ><span class="arrows" >&#11016;</span></td> -->
        </tr>
        
        <tr>
            <td onclick='Left()' ><span class="arrows" >&#8678;</span></td>
            <td onclick='Stop()'><span class="arrows" >&#129197;</td>    
            <td onclick='Right()' ><span class="arrows" >&#8680;</span></td>
        </tr>
        
        <tr>
            <!-- <td onclick='onTouchStartAndEnd("7")'><span class="arrows" >&#11019;</span></td> -->
            <td style="background-color:white;box-shadow:none"></td>
            <td onclick='Backward()' ><span class="arrows" >&#8681;</span></td>
            <td style="background-color:white;box-shadow:none"></td>
            <!-- <td onclick='onTouchStartAndEnd("8")' ><span class="arrows" >&#11018;</span></td> -->
        </tr>
        
        <!-- <tr>
            <td onclick='onTouchStartAndEnd("9")' ><span class="circularArrows" >&#8634;</span></td>
            <td style="background-color:white;box-shadow:none"></td>
            <td onclick='onTouchStartAndEnd("10")' ><span class="circularArrows" >&#8635;</span></td>
        </tr> -->
        </table>
    </div>
    <script>
        /*var i=0;
        function onTouchStartAndEnd(value) {
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                  document.getElementById("temperature").innerHTML = this.responseText;
                  
              //console.log(this.responseText);
              if(chartT.series[0].data.length > 40) {
                chartT.series[0].addPoint([x, y], true, true, true);
              } else {
                chartT.series[0].addPoint([x, y], true, false, true);
              }
            }
          };
          xhttp.open("GET", "/temperature", true);
          xhttp.send();
          document.getElementById("temperature").innerHTML = value+" "+i;
          i++;
        }*/

        function Forward() {
            document.getElementById("temperature").innerHTML = "forward";
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("temperature").innerHTML = "forward";
                //   document.getElementById("temperature").innerHTML = this.responseText;
            }
          };
          xhttp.open("GET", "/forward", true);
          xhttp.send();
        }

        function Backward() {
            document.getElementById("temperature").innerHTML = "backward";
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("temperature").innerHTML = "backward";
                //   document.getElementById("temperature").innerHTML = this.responseText;
            }
          };
          xhttp.open("GET", "/backward", true);
          xhttp.send();
        }

        function Left() {
            document.getElementById("temperature").innerHTML = "left";
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("temperature").innerHTML = "left";
                //   document.getElementById("temperature").innerHTML = this.responseText;
            }
          };
          xhttp.open("GET", "/left", true);
          xhttp.send();
        }

        function Right() {
            document.getElementById("temperature").innerHTML = "right";
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("temperature").innerHTML = "right";
                //   document.getElementById("temperature").innerHTML = this.responseText;
            }
          };
          xhttp.open("GET", "/right", true);
          xhttp.send();
        }

        function Stop() {
            document.getElementById("temperature").innerHTML = "stop";
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("temperature").innerHTML = "stop";
                //   document.getElementById("temperature").innerHTML = this.responseText;
            }
          };
          xhttp.open("GET", "/stop", true);
          xhttp.send();
        }
        
        </script>
</body>

</html>
)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(0.0);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  //dht.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/" , HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/HTML", index_html, processor);
  });

  server.on("/forward" , HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Forward");
    request->send_P(200, "text/plain", String(h).c_str());
  });
  

  // Start server
  server.begin();
}
 
void loop(){  
  /* long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    // Read temperature as Celsius (the default)
    float newT = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //float newT = dht.readTemperature(true);
    // if temperature read failed, don't change t value
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      h = newH;
      Serial.println(h);
    }
  }*/
}

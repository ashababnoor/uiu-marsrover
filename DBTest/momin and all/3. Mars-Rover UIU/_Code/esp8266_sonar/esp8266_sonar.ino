
//Front Sonar
const int trigPin = 5; //D1
const int echoPin = 16; //D0

//const int led = 0;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034


long duration;
float distanceCm;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 // pinMode(led, OUTPUT);

  //digitalWrite(led, LOW);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.println("");

  
//  if(distanceCm <= 15.00){
//     Serial.print("Distance (cm): ");
//    Serial.println(distanceCm);
//    Serial.println("");
//
//    digitalWrite(led, HIGH);
//    delay(500);
//    digitalWrite(led, LOW);
//  }
//
//  else if(distanceCm > 15.00 && distanceCm <= 500){
//    // Prints the distance on the Serial Monitor
//    Serial.print("Distance (cm): ");
//    Serial.println(distanceCm);
//    Serial.println("");
//
//    digitalWrite(led, LOW);
//  }
//  else{
//    
//  }


  delay(500);
}

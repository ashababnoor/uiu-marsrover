#define SOUND_VELOCITY 0.034

//Front Sonar
const int trigPin = 5; //D1
const int echoPin = 16; //D0

//Back Sonar
const int trigPin_2 = 2; //D4
const int echoPin_2 = 13; //D7

int maxSpeed = 50;

int Rmtr_F = 14; //D5
int Rmtr_B = 4; // D2
int Lmtr_F = 12; // D6
int Lmtr_B = 15; // D8

long duration;
float distanceCm;

long duration_2;
float distanceCm_2;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin_2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_2, INPUT); // Sets the echoPin as an Input
  
  pinMode(Lmtr_F, OUTPUT);
  pinMode(Lmtr_B, OUTPUT);
  pinMode(Rmtr_F, OUTPUT);
  pinMode(Rmtr_B, OUTPUT);
}

void loop() {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin_2, LOW);
    delayMicroseconds(2);
  
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin_2, LOW);
  
     // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    duration_2 = pulseIn(echoPin_2, HIGH);
    
    // Calculate the distance
    distanceCm = duration * SOUND_VELOCITY/2;
    distanceCm_2 = duration_2 * SOUND_VELOCITY/2;
  
    if(distanceCm <= 15.00){
      Serial.print("Distance 1st sonar (cm): ");
      Serial.println(distanceCm);
      Serial.println("");
  
      moveBackSlow();
      Break();
    }
     else if(distanceCm > 15.00 && distanceCm <= 50){
      // Prints the distance on the Serial Monitor
      Serial.print("Distance 1st sonar (cm): ");
      Serial.println(distanceCm);
      Serial.println("");
  
      moveForwardSlow();
      Break();
    }
  
    if(distanceCm_2 <= 15.00){
      Serial.print("Distance 2nd sonar (cm): ");
      Serial.println(distanceCm_2);
      Serial.println("");
  
      moveBackFast();
      Break();
    }
     else if(distanceCm_2 > 15.00 && distanceCm_2 <= 50){
      // Prints the distance on the Serial Monitor
      Serial.print("Distance 2nd sonar (cm): ");
      Serial.println(distanceCm_2);
      Serial.println("");
  
      moveForwardFast();
      Break();
    }
  
  delay(1000);
}



void moveForwardFast(){
  maxSpeed = 150;
  analogWrite(Lmtr_F, maxSpeed);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, maxSpeed);
  analogWrite(Rmtr_B, 0);
  delay(1000);
}

void moveBackFast(){
  maxSpeed = 150;
  analogWrite(Lmtr_F, 0);
  analogWrite(Lmtr_B, maxSpeed);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, maxSpeed);
  delay(1000);
}

void Break(){
  analogWrite(Lmtr_F, 0);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, 0);
  delay(300);
}

void moveForwardSlow(){
  maxSpeed = 50;
  analogWrite(Lmtr_F, maxSpeed);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, maxSpeed);
  analogWrite(Rmtr_B, 0);
  delay(1000);
}

void moveBackSlow(){
  maxSpeed = 50;
  analogWrite(Lmtr_F, 0);
  analogWrite(Lmtr_B, maxSpeed);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, maxSpeed);
  delay(1000);
}

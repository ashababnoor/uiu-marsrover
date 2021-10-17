//Controling robot movement front and back using ultrasonic

#define SOUND_VELOCITY 0.034

//Front Sonar
const int trigPin = 5; //D1
const int echoPin = 16; //D0

int maxSpeed = 50;

int Rmtr_F = 14; //D5
int Rmtr_B = 4; // D2
int Lmtr_F = 12; // D6
int Lmtr_B = 15; // D8

long duration;
float distanceCm;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  pinMode(Lmtr_F, OUTPUT);
  pinMode(Lmtr_B, OUTPUT);
  pinMode(Rmtr_F, OUTPUT);
  pinMode(Rmtr_B, OUTPUT);
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

    if(distanceCm <= 10.00){
       Serial.print("Distance 1st sonar (cm): ");
       Serial.println(distanceCm);
       Serial.println("");
      
      Break();
    }
  
    else if(distanceCm  > 10.00 && distanceCm <= 30.00){
      Serial.print("Distance 1st sonar (cm): ");
      Serial.println(distanceCm);
      Serial.println("");
      
      moveBackSlow();
      Break();
    }
     else if(distanceCm > 30.00 && distanceCm <= 65){
      // Prints the distance on the Serial Monitor
      Serial.print("Distance 1st sonar (cm): ");
      Serial.println(distanceCm);
      Serial.println("");
  
      moveForwardSlow();
      Break();
    }
    else if(distanceCm > 60){
      Serial.print("Distance 1st sonar (cm): ");
      Serial.println(distanceCm);
      Serial.println("");
      
      rotateRight();
      Break();
    }

    delay(1700);
}

void moveForwardSlow(){
  maxSpeed = 50;
  analogWrite(Lmtr_F, maxSpeed);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, maxSpeed);
  analogWrite(Rmtr_B, 0);
  delay(800);
}

void moveBackSlow(){
  maxSpeed = 50;
  analogWrite(Lmtr_F, 0);
  analogWrite(Lmtr_B, maxSpeed);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, maxSpeed);
  delay(2000);
}

void rotateRight(){
  maxSpeed = 50;
  analogWrite(Lmtr_F, maxSpeed);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, maxSpeed);
  delay(800);
}

void Break(){
  analogWrite(Lmtr_F, 0);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, 0);
  delay(500);
}

//void moveForwardFast(){
//  maxSpeed = 150;
//  analogWrite(Lmtr_F, maxSpeed);
//  analogWrite(Lmtr_B, 0);
//  analogWrite(Rmtr_F, maxSpeed);
//  analogWrite(Rmtr_B, 0);
//  delay(1000);
//}
//
//void moveBackFast(){
//  maxSpeed = 150;
//  analogWrite(Lmtr_F, 0);
//  analogWrite(Lmtr_B, maxSpeed);
//  analogWrite(Rmtr_F, 0);
//  analogWrite(Rmtr_B, maxSpeed);
//  delay(1000);
//}

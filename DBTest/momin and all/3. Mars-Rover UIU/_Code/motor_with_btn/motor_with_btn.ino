/*
  UIU Mars-Rover ->Hardware-software Group-1
  [Motor Movement with Button using Arduino] 
 */

// Arduino Model: Arduino Mega
#define motorSpeed 150


//Motor PWM PIN
int leftMotor_F = 4,  leftMotor_B = 5,  rightMotor_F = 6, rightMotor_B = 7;  
//Robot movement button
int moveFor_btn = 34, moveBack_btn = 36, moveLeft_btn = 38, moveRight_btn = 40;


void setup() {
  pinMode(moveFor_btn, INPUT);
  pinMode(moveBack_btn, INPUT);     // button to control the movement of the robot
  pinMode(moveLeft_btn, INPUT);
  pinMode(moveRight_btn, INPUT);

  pinMode(leftMotor_B, OUTPUT);
  pinMode(leftMotor_F, OUTPUT);     // Motor control pins
  pinMode(rightMotor_F, OUTPUT);
  pinMode(rightMotor_B, OUTPUT);
}

void loop() {
                                               
     while(digitalRead(moveFor_btn) != LOW){
        moveForward();                                    
     }
     while(digitalRead(moveBack_btn) != LOW){ 
        moveBackward();
     }
     while(digitalRead(moveLeft_btn) != LOW){               // move left until left button is released
        moveLeft();
     }
     while(digitalRead(moveRight_btn) != LOW){
        moveRight();
     }
     
     Brake();
}

//Function of Motor Movement
void moveForward(){
  analogWrite(leftMotor_F, motorSpeed);
  analogWrite(rightMotor_F, motorSpeed);
}
void moveBackward(){
  analogWrite(leftMotor_B, motorSpeed);
  analogWrite(rightMotor_B, motorSpeed);
}
void moveLeft(){
  analogWrite(leftMotor_B, motorSpeed);
  analogWrite(rightMotor_F, motorSpeed);
}
void moveRight(){
  analogWrite(leftMotor_F, motorSpeed);
  analogWrite(rightMotor_B, motorSpeed);
}
void Brake(){
  analogWrite(leftMotor_F, 0);
  analogWrite(rightMotor_F, 0);
  analogWrite(leftMotor_B, 0);
  analogWrite(rightMotor_B, 0);
}

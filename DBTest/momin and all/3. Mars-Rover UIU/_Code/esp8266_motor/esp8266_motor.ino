int maxSpeed = 50;

int Rmtr_F = 14; //D5
int Rmtr_B = 4; // D2
int Lmtr_F = 12; // D6
int Lmtr_B = 15; // D8


void setup() {
  // put your setup code here, to run once:
  pinMode(Lmtr_F, OUTPUT);
  pinMode(Lmtr_B, OUTPUT);
  pinMode(Rmtr_F, OUTPUT);
  pinMode(Rmtr_B, OUTPUT);
}

void loop() {
  maxSpeed = 50;
  // put your main code here, to run repeatedly:   
  analogWrite(Lmtr_F, maxSpeed);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, maxSpeed);
  analogWrite(Rmtr_B, 0);
  delay(5000);

  analogWrite(Lmtr_F, 0);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, 0);
  delay(2000);

  analogWrite(Lmtr_F, 0);
  analogWrite(Lmtr_B, maxSpeed);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, maxSpeed);
  delay(5000);


  analogWrite(Lmtr_F, 0);
  analogWrite(Lmtr_B, 0);
  analogWrite(Rmtr_F, 0);
  analogWrite(Rmtr_B, 0);
  delay(2000);
}

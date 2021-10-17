int pin = D3;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin, HIGH);
  delay(300);
  Serial.println("\nLED ON");
  digitalWrite(pin, LOW);
  delay(300);
  Serial.println("\nLED OFF");
}

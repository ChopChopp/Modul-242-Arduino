/*
  Autor:        Umut Oeztuerk
  Version:      1.0
  Beschreibung: Dieser Code beschreibt eine Arduino Schaltung, welches einen Party Trick mit einem Touch sensor darstellt.
  */

void setup() {
 pinMode(2, INPUT);
 Serial.begin(9600);
 pinMode(0, OUTPUT);
 pinMode(1, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
}
void loop() {
 if (digitalRead(2) == HIGH) {
  Serial.println("Sensor is touched");
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  delay(500);
 } else {
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
 }
}

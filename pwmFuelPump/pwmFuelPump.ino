void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}

void loop() {
  for (int i = 0; i < 10; i++) {
      analogWrite(10, i*20);
      delay(100);
  }
}

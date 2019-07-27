#define PIN_DATA_INPUT 11


void setup() {
  pinMode(PIN_DATA_INPUT, INPUT);
  Serial.begin(9600);
}

void loop() {
  int state = digitalRead(PIN_DATA_INPUT);
  Serial.print("state:"); Serial.println(state);

  delay(10);
}

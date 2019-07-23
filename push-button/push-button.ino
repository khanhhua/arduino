#define BUTTON_PIN 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int button = digitalRead(BUTTON_PIN);
  Serial.print("=>");
  Serial.println(button);

  delay(5000);
}

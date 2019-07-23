/**
 * You'll learn:
 * - 8-bit shift register
 * - PWM pins for Arduino Nano
 * 
 * @see https://weworkweplay.com/play/practical-guide-to-shift-registers/
 * @see https://techtutorialsx.com/2016/08/30/esp8266-connection-to-sn74hc595/
 * @see https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
 */
// Send data here serially
#define DATA_PIN 2
// Latch pin - sn74hc545 - pin 12
#define PWM_PIN_RCLK 3
// Serial clock - sn74hc545 - pin 11
#define PWM_PIN_SRCLK 11

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(PWM_PIN_RCLK, OUTPUT); 
  pinMode(PWM_PIN_SRCLK, OUTPUT);
}

void loop() {
  for (byte i=0; i<=255; i++) {
    writeByte(i);
    delay(200);  
  }
}

void writeByte(byte data) {
  Serial.print("data: "); Serial.println(data);

  digitalWrite(PWM_PIN_RCLK, LOW); // latch off
  digitalWrite(DATA_PIN, LOW);

  for (int i=0; i<=7; i++) {
    Serial.print("shift: "); Serial.println(data & (1 << i));
    byte nextBit = (data & (1 << i)) > 0 ? HIGH: LOW;
    Serial.print("bit: "); Serial.println(nextBit);
    
    digitalWrite(PWM_PIN_SRCLK, LOW); // Lower clock edge
    digitalWrite(DATA_PIN, nextBit);
    digitalWrite(PWM_PIN_SRCLK, HIGH); // Higher clock edge
    digitalWrite(DATA_PIN, LOW);
  }
  
  digitalWrite(PWM_PIN_SRCLK, LOW); 
  digitalWrite(PWM_PIN_RCLK, HIGH); // latch on
}

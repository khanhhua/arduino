#define PIN_DATA_INPUT 11

#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

void setup() {
  Serial.begin(9600);

  if (!driver.init()) {
    Serial.println("init failed");
  } else {
    driver.setModeRx();
    Serial.print("Speed"); Serial.println(driver.speed());
    Serial.println("receiving...");
  }
}

void loop() {
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) {
    int i;

    Serial.print("Message:"); Serial.println((char*)buf);
  } else {
    Serial.println("Nothing");
  }

  delay(5000);
}

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define MODE_RUNNING 1
#define MODE_ADJ_HOUR 2
#define MODE_ADJ_MIN 3

#define PIN_MODE_INTERRUPT 2
#define PIN_ADJUST_UP 3
#define PIN_ADJUST_DOWN 4

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int mode = MODE_RUNNING;

int minute = 0;
int hour = 0;
int second = 0;

void interrupt(void) {
  switch (mode) {
    case MODE_RUNNING: mode = MODE_ADJ_HOUR; break;
    case MODE_ADJ_HOUR: mode = MODE_ADJ_MIN; break;
    case MODE_ADJ_MIN: mode = MODE_RUNNING; break;
    default: return;
  }
}

void setup() {
  pinMode(PIN_MODE_INTERRUPT, INPUT);
  pinMode(PIN_ADJUST_UP, INPUT);
  pinMode(PIN_ADJUST_DOWN, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(2), interrupt, RISING);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Schoenen Tag!   ");
  lcd.setCursor(0, 1);

  String output = format(hour, minute, second);
  lcd.print(output);
  delay(1000);
}

void loop() {
  if (mode == MODE_RUNNING) {
    running();
  } else {
    adjusting();
  }
}

String format(int h, int m, int s) {
  String hString = String(h);
  String mString = String(m);
  String sString = String(s);

  String output = "00:00:00";
  if (hString.length() == 2) {
    output[0] = hString[0];
    output[1] = hString[1];
  } else {
    output[1] = hString[0];
  }
  if (mString.length() == 2) {
    output[3] = mString[0];
    output[4] = mString[1];
  } else {
    output[4] = mString[0];
  }
  if (sString.length() == 2) {
    output[6] = sString[0];
    output[7] = sString[1];
  } else {
    output[7] = sString[0];
  }

  return output;
}

void running(void) {
  second += 1;
  if (second == 60) {
    minute += 1;
    second = 0;
  }

  if (minute == 60) {
    hour += 1;
    minute = 0;
  }

  if (hour == 24) {
    hour = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print("Schoenen Tag!   ");

  String output = format(hour, minute, second);
  lcd.setCursor(0, 1);
  
  lcd.print(output);
  delay(1000);
}

void adjusting(void) {
  int buttonUp = digitalRead(PIN_ADJUST_UP);
  int buttonDown = digitalRead(PIN_ADJUST_DOWN);

  if (mode == MODE_ADJ_HOUR) {
    lcd.setCursor(0, 0);
    lcd.print("Setting hour   ");
    
    hour = buttonUp == HIGH ? (hour + 1) : (buttonDown == HIGH ? hour - 1 : hour);
    if (hour < 0) {
      hour = 23;
    } else if (hour >= 24) {
      hour = 0;
    }
  } else if (mode == MODE_ADJ_MIN) {
    lcd.setCursor(0, 0);
    lcd.print("Setting minute   ");

    minute = buttonUp == HIGH ? (minute + 1) : (buttonDown == HIGH ? minute - 1 : minute);
    if (minute < 0) {
      minute = 59;
    } else if (minute >= 60) {
      minute = 0;
    }
  }

  String output = format(hour, minute, second);
  lcd.setCursor(0, 1);
  lcd.print(output);

  delay(100);
}

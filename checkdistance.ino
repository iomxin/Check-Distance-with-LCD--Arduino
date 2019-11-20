#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>
#include <Wire.h>

#define button1 2
#define button2 3
#define buzzer 13
#define ultratrig 11
#define ultraecho 12
LiquidCrystal_I2C lcd(0x27, 16, 2);
Bounce btn1 = Bounce();
Bounce btn2 = Bounce();
Bounce btn3 = Bounce();

int mode = 1;
float cm = 0;
float duration=0;
float distance=0;
float a;
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  pinMode(buzzer, OUTPUT);
  pinMode(ultratrig, OUTPUT);
  pinMode(ultraecho, INPUT);
  
  pinMode(button1, INPUT_PULLUP);
  btn1.attach(button1);
  btn1.interval(5);

  pinMode(button2, INPUT_PULLUP);
  btn2.attach(button2);
  btn2.interval(5);
  digitalWrite(buzzer,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(1,0);
  lcd.print("Check Distance");
  lcd.setCursor(4,1);
  digitalWrite(11,LOW);
  delayMicroseconds(2);
  digitalWrite(11,HIGH);
  delayMicroseconds(10);
  digitalWrite(11,LOW);
  duration = pulseIn(12,HIGH);
  distance = (((331.5+(0.61*25))*duration)/2);
  a = distance*0.0001;
  btn1.update();
  if (btn1.fell()) {
    cm = a;
     digitalWrite(buzzer,LOW);
     delay(200);
     digitalWrite(buzzer,HIGH);
     delay(200);
  }
  btn2.update();
  if (btn2.fell()) {
    mode++;
  }
  if (mode > 5) {
    mode = 1;
  }
  lcddisplay();
  lcd.clear();
}
void lcddisplay() {
    if (mode == 1) {
      lcd.print(cm);//cm
      lcd.print(" Cm");
      delay(50);
    }
    if (mode == 2) {
      lcd.print(cm/100);//m
      lcd.print(" Metre");
      delay(50);
    }
    if (mode == 3) {
      lcd.print(cm*0.393701);//inch
      lcd.print(" Inch");
      delay(50);
    }
    if (mode == 4) {
      lcd.print(cm*0.0328084);//foot
      lcd.print(" Foot");
      delay(50);
    }
    if (mode == 5) {
      lcd.print(cm*0.0106361);//yard
      lcd.print(" Yard");
      delay(50);
    }
}

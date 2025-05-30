#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address 0x27, 16 columns, 2 rows

Servo myservo1;
Servo myservo2;

int ir_s1 = 2; // Entry IR sensor
int ir_s2 = 5; // Exit IR sensor

int Total = 4;
int Space;
int flag1 = 0;
int flag2 = 0;

void setup() {
  pinMode(3, OUTPUT);  // Entry LED Green
  pinMode(4, OUTPUT);  // Entry LED Red
  pinMode(6, OUTPUT);  // Exit LED Green
  pinMode(7, OUTPUT);  // Exit LED Red
  
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);

  myservo1.attach(8); // Entry gate
  myservo2.attach(9); // Exit gate (ADDED)
  
  myservo1.write(100); // Close entry gate
  myservo2.write(100); // Close exit gate
  
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("  Car  Parking  ");
  lcd.setCursor(0, 1);
  lcd.print("     System     ");
  delay(2000);
  lcd.clear();

  Space = Total;
}

void loop() {
  digitalWrite(3, LOW);   // Entry Green LED OFF
  digitalWrite(4, HIGH);  // Entry Red LED ON
  digitalWrite(6, LOW);   // Exit Green LED OFF
  digitalWrite(7, HIGH);  // Exit Red LED ON

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total Space: ");
  lcd.print(Total);

  lcd.setCursor(0, 1);
  lcd.print("Have  Space: ");
  lcd.print(Space);
  delay(1000);

  // Entry IR sensor triggered
  if (digitalRead(ir_s1) == LOW && flag1 == 0) {
    if (Space > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(0);   // Open gate
        digitalWrite(3, HIGH); // Green LED ON
        digitalWrite(4, LOW);  // Red LED OFF
        Space = Space - 1;
      }
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Sorry no Space ");
      lcd.setCursor(0, 1);
      lcd.print("   Available     ");
      delay(2000);
    }
  }

  // Exit IR sensor triggered
  if (digitalRead(ir_s2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo2.write(0);   // Open exit gate
      digitalWrite(6, HIGH); // Green LED ON
      digitalWrite(7, LOW);  // Red LED OFF
      Space = Space + 1;
    }
  }

  // Reset both gates after both flags set
  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo1.write(100);
    myservo2.write(100);
    flag1 = 0;
    flag2 = 0;
  }

  // Safety check
  if (Space > Total) {
    Space = Total;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total empty");
    delay(2000);
  }
}

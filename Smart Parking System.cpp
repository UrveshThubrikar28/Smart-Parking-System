#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <Servo.h> //includes the servo library

Servo myservo1;
Servo myservo2;
int ir_s1 = 2;
int ir_s2 = 5;

int Total = 4;
int Space;
int maxcars = 4;

int flag1 = 0;
int flag2 = 0;

void setup()
{
pinMode(3,OUTPUT); 
pinMode(4,OUTPUT); 
pinMode(6,OUTPUT); 
pinMode(7,OUTPUT);  
pinMode(ir_s1, INPUT);
pinMode(ir_s2, INPUT);
  
myservo1.attach(8);
myservo1.write(100);

lcd.init();                      // initialize the lcd 
lcd.backlight();  
lcd.setCursor (0,0);
lcd.print("  Car  Parking  ");
lcd.setCursor (0,1);
lcd.print("     System     ");
delay(2000);
lcd.clear();


Space = Total;
}

void loop()
{ 
digitalWrite(3,LOW);
digitalWrite(4,HIGH);
digitalWrite(6,LOW);
digitalWrite(7,HIGH);

lcd.clear();
lcd.setCursor (0,0);
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Have  Space: ");
lcd.print(Space);
delay(1000);

if(digitalRead (ir_s1) == LOW && flag1==0)
{
if(Space>0){flag1=1;
if(flag2==0)
{
  myservo1.write(0);
  myservo2.write(0);
  Space = Space-1;
  }
}
else
{
  
lcd.setCursor (0,0);
lcd.print(" Sorry not Space ");  
lcd.setCursor (0,1);
lcd.print("    Available    "); 
delay (1000);

}
}

if(digitalRead (ir_s2) == LOW && flag2==0)
{
  flag2=1;
if(flag1==0)
{
  myservo1.write(0);
  myservo2.write(0);
  Space = Space+1;
  }
}


if(flag1==1 && flag2==1)
{
delay (1000);
myservo1.write(100);
myservo2.write(100);
flag1=0, flag2=0;
}
if (Space > 4){
  maxcars;
  Space = Total;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Total empty");
  delay(2000);
}
}
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
Adafruit_LiquidCrystal lcd(0);
const int servoPin = 3;
int PASSWORD;
int pos;
const int triggPin = 9;
const int echoPin=10;
float distance;
long duration;
Servo servo1;
int piezoPin = 12;
void setup(){ 
servo1.attach(servoPin);
Serial.begin(9600);
lcd.begin(16,2);
pinMode(piezoPin,OUTPUT);  
pinMode(triggPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop() {
ultrasonic_sensor();
  
  if (distance>=300){
    lcd.setBacklight(0);
  }
  else{
    lcd.setBacklight(1);
  }
  delay(1000);
if (distance >=0 && distance <=290 ){
lcd.setCursor(3,0);  
lcd.print(" WELCOME ");
delay (2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Please Enter Pin");
while (Serial.available() == 0){}
 PASSWORD = Serial.parseInt();
 if (PASSWORD == 8520){
  Rightpasscode();
  for (pos = 90; pos <= 180; pos += 1) { 
    servo1.write(pos); 
    delay (10);
  }
   lcd.setCursor(0,0);
   lcd.print("DOOR UNLOCKED");
   tone(piezoPin, 300, 500);
  delay(10000);
   lcd.clear();
for (pos = 180; pos >= 90; pos -= 1) {
    servo1.write(pos);
    delay(10);
 }
  lcd.setCursor(0,1);
  lcd.print("DOOR LOOCKED");
  tone(piezoPin, 300, 500);
  delay(500);
  lcd.clear();
}  
  
  else{ 
 Wrongpasscode();
  }
 }
}


void Rightpasscode(){
lcd.setCursor(0,1);
lcd.print("RIGHT PIN");
delay(500);
lcd.clear();


}

void Wrongpasscode(){
lcd.setCursor(0,1);
lcd.print("WRONG PIN");
tone(piezoPin, 300, 1000);
delay(1000);
lcd.clear();
 }

void ultrasonic_sensor(){
   digitalWrite(triggPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggPin,LOW);

duration = pulseIn(echoPin,HIGH);
distance = duration*0.034 / 2;
/*Serial.print("The Distane of the object from the sensor is ");
Serial.print(distance);
 Serial.println(" cm");*/
 delay(1000);
}




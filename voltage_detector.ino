#include <Servo.h>
int servo=9;
int servoPos=0;
int red;
int blue;
int green;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
red=analogRead(A0);
blue=analogRead(A1);
green=analogRead(A2);
Serial.println(red);

Serial.println(blue);


Serial.println(green);
delay(1000);

}

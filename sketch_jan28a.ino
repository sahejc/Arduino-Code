
#include <IRremote.h>


int trigPin=6;
int echoPin=5;
int pingtime;
int green=8;
int red=7;
int buzz=11;



int mSpeed=255;
float V2;
float voltage;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
   pinMode(A1,INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:


  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  pingtime=pulseIn(echoPin,HIGH);
   voltage= V2/1023*5;
  V2=analogRead(A1);
 Serial.println(pingtime);
  delay(5);
 

 if (pingtime==0){
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(buzz, LOW);
 }
 
  if (pingtime<1000){
digitalWrite(green,LOW);
digitalWrite(red, HIGH);
analogWrite(buzz,10);
delay(500);
digitalWrite(buzz, LOW);
if (pingtime==0){
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(buzz, LOW);
  delay(100000);
 }
}

  if (pingtime>1000){
    digitalWrite(red,LOW);
    digitalWrite(green, HIGH);

}

    
   

} 
    

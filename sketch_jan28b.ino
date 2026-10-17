int speedPin=6;
int di1=4;
int di2=3;
int mSpeed=255;
void setup() {
  // put your setup code here, to run once:
 pinMode(speedPin,OUTPUT);
  pinMode(di1,OUTPUT);
  pinMode(di2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(di1,LOW);
  digitalWrite(di2,HIGH);
  analogWrite(speedPin,170);
}

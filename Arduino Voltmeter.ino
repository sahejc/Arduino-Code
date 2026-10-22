
float V2;
float voltage;
void setup() {
  // put your setup code here, to run once:
 pinMode(A1,INPUT);
 Serial.begin(9600);

 
}

void loop() {
  // put your main code here, to run repeatedly:
  voltage= V2/1023*5;
  V2=analogRead(A1);
  Serial.println(voltage);
  delay(500);
  

}

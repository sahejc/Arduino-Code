
#include <LiquidCrystal.h>

// LCD module connections (change according to your wiring)
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
const int trigPin = 5;    // Trigger pin connected to Arduino pin 2
const int echoPin = 6;    // Echo pin connected to Arduino pin 3
float distance;
int dOld=1;
int dNew;
int count;
int up=A0;
int down=A1;

int increase;
int decrease;



LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  Serial.begin(9600);     // Initialize serial communication at 9600 baud rate
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(up,INPUT);
  pinMode(down,INPUT);

  pinMode(2,OUTPUT);
  count==0;
  
}

void loop() {
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

    increase=analogRead(up);
  decrease=analogRead(down);

  Serial.println(increase);
  Serial.println(decrease);


 
 if(increase<5){
  count++;
  count++;
  count++;
  count++;
  count++;
  lcd.setCursor(0, 1);  
  lcd.print("                ");  
  lcd.setCursor(0, 1);          
  lcd.print(count); 
  lcd.print(" pull up(s)"); 
 }
  if(decrease<5){
    count--;
    count--;
    count--;
    count--;
    count--;
  lcd.setCursor(0, 1);  
  lcd.print("                ");  
  lcd.setCursor(0, 1);          
  lcd.print(count); 
  lcd.print(" pull up(s)"); 

  }
    
   



  // Measure the duration of the pulse from the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the speed of sound
 distance = (duration * 0.01350394) / 2;  // Divide by 2 to get one-way distance

  // Print the distance on the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" in.");

  lcd.print("                ");  // Clear the line
  lcd.setCursor(0, 0);          // Set the cursor to the second line
  lcd.print(distance);          // Display the distance on the LCD
  lcd.print(" in.");
 delay(100);
if(distance<39){
dNew=1;
  
}
else {
  dNew=0;
}
if(dOld==0 && dNew==1){
  count++;
  
    // Clear the line
  lcd.print("                ");  // Clear the line
  lcd.setCursor(0, 1);          // Set the cursor to the second line
  lcd.print(count); 
  lcd.print(" pull up(s)");
  delay(800);

}
dOld=dNew;


 }
 

  

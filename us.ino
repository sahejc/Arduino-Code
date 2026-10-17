const int trigPin = 5;    // Trigger pin connected to Arduino pin 2
const int echoPin = 6;    // Echo pin connected to Arduino pin 3

void setup() {
  Serial.begin(9600);     // Initialize serial communication at 9600 baud rate
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Send a 10us pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse from the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the speed of sound
  float distance = (duration * 0.0343) / 2;  // Divide by 2 to get one-way distance

  // Print the distance on the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);  // Delay for a second before taking the next measurement
}

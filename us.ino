const int trigPin = 5;    // Trigger pin connected to Arduino pin 5
const int echoPin = 6;    // Echo pin connected to Arduino pin 6

const int NUM_SAMPLES = 5;           // Readings averaged per measurement
const unsigned long TIMEOUT_US = 30000;  // 30 ms timeout (~5 m max range)

void setup() {
  Serial.begin(9600);     // Initialize serial communication at 9600 baud rate
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// Takes one measurement. Returns distance in cm, or -1 if no echo was received.
float readDistance() {
  // Send a 10 us pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo pulse duration, giving up after the timeout
  long duration = pulseIn(echoPin, HIGH, TIMEOUT_US);

  if (duration == 0) {
    return -1;  // No echo: out of range or sensor not responding
  }

  // Speed of sound ~0.0343 cm/us; divide by 2 for one-way distance
  return (duration * 0.0343) / 2;
}

void loop() {
  float sum = 0;
  int valid = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    float d = readDistance();
    if (d > 0) {
      sum += d;
      valid++;
    }
    delay(60);  // Let echoes die down between pings
  }

  if (valid > 0) {
    Serial.print("Distance: ");
    Serial.print(sum / valid);
    Serial.println(" cm");
  } else {
    Serial.println("Out of range / no echo");
  }

  delay(1000);  // Wait before the next measurement
}

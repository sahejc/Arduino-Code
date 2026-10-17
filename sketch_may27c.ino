#include <DHT.h>

#define DHTPIN 2       // Pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11  // DHT sensor type

DHT dht(DHTPIN, DHTTYPE);

float Fahr;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  dht.begin();         // Initialize DHT sensor
}

void loop() {
  delay(2000);  // Delay between readings

  float humidity = dht.readHumidity();     // Read humidity value
  float temperature = dht.readTemperature();  // Read temperature value in Celsius

  Fahr=temperature*1.8+32;

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity values
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(Fahr);
  Serial.println("°F");
}

#include <DHT.h>
#include <DHT_U.h>





#define DHTPIN 2      
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);
}
int RPM

void setup() {
  // put your setup code here, to run once:

pinMode(A0,INPUT);
Serial.begin(9600); 
  dht.begin();        
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);  // Delay between readings

  float humidity = dht.readHumidity();     // Read humidity value
  float temperature = dht.readTemperature();  // Read temperature value in Celsius

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
  Serial.print(temperature);
  Serial.println("°C");

  RPM=analogRead(A0);
  Serial.println(RPM);
  delay(250);

}

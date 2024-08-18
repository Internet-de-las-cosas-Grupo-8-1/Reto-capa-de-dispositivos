#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 4
DHT dht(dht_dpin, DHTTYPE);

#define LED D1 // LED
#define LIGHT_SENSOR_PIN A0 // Pin analógico 

int ValueRead = 2;
int myflag = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW); // LED comienza apagado
}

void loop()
{
  if (Serial.available()) {
    ValueRead = Serial.parseInt();
  }
  
  if (((ValueRead == 1 && myflag == 0) || myflag == 1) && !(ValueRead == 2 && myflag == 1)) {
    digitalWrite(LED, HIGH);  // Se prende el LED
    Serial.println("Prendido");
    myflag = 1;
  } else {
    digitalWrite(LED, LOW);   // Se apaga el LED
    Serial.println("Apagado");
    myflag = 0;
  }
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int lightValue = analogRead(LIGHT_SENSOR_PIN); 
  
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.println("C  ");
  
  Serial.print("Light intensity = ");
  Serial.println(lightValue); 
  
  delay(1000); // Espera de 1 segundo 
}

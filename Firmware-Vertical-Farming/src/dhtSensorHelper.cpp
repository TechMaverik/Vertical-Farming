#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>

float getCurrentTemp(DHT dht){    
    float temperature = dht.readTemperature();
    return temperature;
}

float getCurrentHumidity(DHT dht){
    float humidity = dht.readHumidity();
    return humidity;
}
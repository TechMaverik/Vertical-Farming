#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>


#include "displayMsgHelper.h"
#include "gasSensorHelper.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define MQ2_PIN 18
#define DHTPIN 19      
#define DHTTYPE DHT11

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600);
  Wire.begin(21, 22); // SDA=21, SCL=22
  dht.begin();
  pinMode(MQ2_PIN, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  loadIntrMsg(display);
  delay(2000);
  
  
}

void loop() {   
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Farming");
  display.display();
  
  bool state=detectedHydoCarbonPresence(MQ2_PIN);
  Serial.println(state);
  if(state==true)
  {
    display.setCursor(0, 25);
    display.setTextSize(1);
    display.println("Hydrocarbon: Absent");
    display.display();
  }
  else
  {
    display.setCursor(0, 25);
    display.setTextSize(1);
    display.println("Hydrocarbon: Present");
    display.display();
  }
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  display.setCursor(0, 35);
  display.setTextSize(1);
  display.println("Temperature:");
  display.setCursor(72, 35);
  display.print(temperature);
  display.setCursor(110, 35);
  display.print("C ");
  display.display();

  display.setCursor(0, 45);
  display.setTextSize(1);
  display.println("Humidity:");
  display.setCursor(68, 45);
  display.print(humidity);
  display.setCursor(100, 45);
  display.print("%");
  display.display();

  display.setCursor(0, 45);
  display.setTextSize(1);
  display.println("Relay:");
  display.setCursor(68, 45);
  display.print(humidity);
  display.setCursor(100, 45);
  display.print("%");
  display.display();

  delay(5000);
}

#include <Wire.h>
#include <WiFi.h>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "displayDriver.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  Serial.begin(9600);
  checkDisplay(display);
  display.clearDisplay(); 
  showMsg(display,"V-Farming",0,0,1);
  showMsg(display,"built in AI & DNT LAB",1,0,1);  
  showMsg(display,"DPS-Indirapuram",2,0,1);
  delay(3000);
  Serial.println("Vertical Farming");
  Serial.println("Built in AI & DNT LAB");
  Serial.println("DPS-Indirapuram");
}

void loop()
{
  
}
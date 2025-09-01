#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDRESS 0x3C

void checkDisplay(Adafruit_SSD1306 display)
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // Stay here
  }
}

bool showMsg(Adafruit_SSD1306 display, String msg, int posx, int posy, int size)
{
    display.setTextSize(size); 
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(posx, posy);         
    display.println(msg);
    display.display(); 
}
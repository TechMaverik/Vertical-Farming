#include <Arduino.h>
#include <Adafruit_SSD1306.h>

void loadIntrMsg(Adafruit_SSD1306 display)
{
    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("V-Farming");
  display.setCursor(0, 30);
  display.setTextSize(1);
  display.println("Built in AI & D&T Lab");
  display.setCursor(0, 50);
  display.setTextSize(1);
  display.println("DPS-Indirapuram 2025");
  display.display();
}
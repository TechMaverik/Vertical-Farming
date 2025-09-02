#include <Arduino.h>
#include <Adafruit_SSD1306.h>

void loadIntrMsg(Adafruit_SSD1306 display)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Farming");
    display.setCursor(0, 30);
    display.setTextSize(1);
    display.println("Built in AI & D&T Lab");
    display.setCursor(0, 50);
    display.setTextSize(1);
    display.println("DPS-Indirapuram 2025");
    display.display();
}

void loadIntrMsg2(Adafruit_SSD1306 display)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Farming");
    display.display();
}

void hydrocarbon_present(Adafruit_SSD1306 display)
{
    display.setCursor(0, 25);
    display.setTextSize(1);
    display.println("Hydrocarbon: Absent");
    display.display();
}

void hydrocarbon_absent(Adafruit_SSD1306 display)
{
    display.setCursor(0, 25);
    display.setTextSize(1);
    display.println("Hydrocarbon: Present");
    display.display();
}

void display_temp_humidity(Adafruit_SSD1306 display, float temperature, float humidity)
{
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

    display.setCursor(0, 55);
    display.setTextSize(1);
    display.println("Pump: OFF");
    display.display();
}
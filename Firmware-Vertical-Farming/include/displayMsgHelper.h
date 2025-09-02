#include <Arduino.h>
#include <Adafruit_SSD1306.h>

void loadIntrMsg(Adafruit_SSD1306 display);
void loadIntrMsg2(Adafruit_SSD1306 display);
void hydrocarbon_present(Adafruit_SSD1306 display);
void hydrocarbon_absent(Adafruit_SSD1306 display);
void display_temp_humidity(Adafruit_SSD1306 display, float temperature, float humidity);
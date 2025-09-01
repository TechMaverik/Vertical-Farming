#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#pragma

void checkDisplay(Adafruit_SSD1306 display); 
bool showMsg(Adafruit_SSD1306 display, String msg, int posx, int posy, int size);
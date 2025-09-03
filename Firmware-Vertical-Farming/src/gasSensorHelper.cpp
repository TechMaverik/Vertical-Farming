#include <Arduino.h>

bool detectedHydoCarbonPresence(int pin)
{
    int gasState = digitalRead(pin);    
    return gasState;
}
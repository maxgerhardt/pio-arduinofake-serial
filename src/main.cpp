#include "Arduino.h"

void setup()
{
    Serial.begin(9600); // startup serial
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    if(Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        if (input == "turnon") {
            digitalWrite(LED_BUILTIN, HIGH);
        } else if (input == "turnoff") {
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}


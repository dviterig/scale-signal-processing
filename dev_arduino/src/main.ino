#include "sensors/Scale.h"

Scale scale;

void setup() {
    Serial.println("Starting...");
    Serial.begin(9600);
    scale.begin();
}

void loop() {
    if (scale.hasReading()) {
        float reading = scale.getReading();
        Serial.print("  received reading: ");
        Serial.println(reading);
    }
}

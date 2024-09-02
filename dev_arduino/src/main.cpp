#include "MockArduino.h"
#include <iostream>
#include "constants.h"

// The main.cpp contains a simple main() which simulates how a normal Arduino sketch
// would get called (by calling a setup() once, and then indentfinitely calling loop()).
// There is no need to modify this file.

#include "main.ino"

int main()
{
    setup();

    while (true)
    {
        loop();
        delay(SIMULATE_DELAY_MS);
    }

    return 0;
}

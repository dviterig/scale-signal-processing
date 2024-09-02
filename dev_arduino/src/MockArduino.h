#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

#include <stdint.h>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>

// Common Arduino functions
unsigned long millis();
void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);
unsigned long micros();

// Mock Serial class
class MockSerial
{
public:
    void begin(unsigned long baud);

    template <typename T>
    void print(const T &value)
    {
        std::cout << value;
    };

    template <typename T>
    void println(const T &value)
    {
        std::cout << value << std::endl;
    };
};

// Global instance of MockSerial to mimic Arduino Serial
extern MockSerial Serial;

#endif // MOCK_ARDUINO_H

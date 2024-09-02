#include "MockArduino.h"
#include <map>
#include <chrono>
#include <thread>

static std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();

// Time functions
unsigned long millis()
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
}

void delay(unsigned long ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void delayMicroseconds(unsigned int us)
{
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}

unsigned long micros()
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - startTime).count();
}

// Mock Serial class implementation
void MockSerial::begin(unsigned long baud)
{
    // For mocking, we do nothing here
}

// Global instance of MockSerial
MockSerial Serial;

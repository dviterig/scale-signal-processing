#ifndef SIGNALPROCESSOR_H
#define SIGNALPROCESSOR_H

#include <vector>
#include <functional>
#include <thread>
#include <mutex>

#include "timer/Timer.h"

// DataPoint struct definition
struct DataPoint {
    double data;
    long timestamp; // milliseconds since epoch
};

// SignalProcessor class definition
class SignalProcessor {
private:
    // States
    enum State { Stabilizing, Stable };
    State currentState;

    long stabilizationTime; // in milliseconds
    DataPoint lastAddedData;
    DataPoint lastStableData;
    Timer timer;

    // State machine handler
    void onTimeout();

    // Placeholder for the output data callback
    std::function<void(long, double, long, double)> outputCallback;

public:
    // Constructor
    SignalProcessor(double minOutput, long stabilizationTimeMs);

    // Destructor
    ~SignalProcessor();

    // Method to add data to the vector
    void addData(double data, long timestamp);

    // Subscribe to the output data callback
    void subscribeToOutput(std::function<void(long, double, long, double)> callback);
};

#endif // SIGNALPROCESSOR_H

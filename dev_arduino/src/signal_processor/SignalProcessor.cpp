#include "SignalProcessor.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>

// Constructor
SignalProcessor::SignalProcessor(double minOutput, long stabilizationTimeMs)
    : stabilizationTime(stabilizationTimeMs), currentState(Stable), lastStableData({0.0, 0}) {}

// Destructor
SignalProcessor::~SignalProcessor() {
    timer.stop();
}

// State machine handler
void SignalProcessor::onTimeout() {
    if (currentState == Stabilizing) {
        std::cout << "\nState: Stabilizing -> Stable\n" << std::endl;
        currentState = Stable;
    }
    outputCallback(lastStableData.timestamp, lastStableData.data, lastAddedData.timestamp, lastAddedData.data);
    lastStableData = lastAddedData;
}

// Method to add data to the vector
void SignalProcessor::addData(double data, long timestamp) {
    lastAddedData = {data, timestamp};

    switch (currentState) {
    case Stable:
        std::cout << "\nState: Stable -> Stabilizing\n" << std::endl;
        currentState = Stabilizing;
        timer.startSingleShot(std::chrono::milliseconds(stabilizationTime), [this]() { this->onTimeout(); });
        break;

    case Stabilizing:
        timer.restart(std::chrono::milliseconds(stabilizationTime));
        break;
    }
}

// Subscribe to the output data callback
void SignalProcessor::subscribeToOutput(std::function<void(long, double, long, double)> callback) {
    outputCallback = callback;
}

#ifndef SCALE_H
#define SCALE_H

#include <vector>
#include "signal_processor/SignalProcessor.h"

// WeightItem is used internall to store an absolute time difference and weight for each
// (to be simulated) weight record.
struct WeightItem {
    long time_diff;
    float weight;
};

// The Scale class simulates a typical Arduino scale (load cell) interfacing class.
class Scale
{
public:
    Scale();
    void begin();

    // hasReading returns true if a next reading is available, false otherwise.
    bool hasReading();

    // getReading returns the available reading (or 0 if no reading is available)
    float getReading();

private:
    std::vector<WeightItem> _weight_items;
    int _last_read_index;
    unsigned long _millis_offset;
    SignalProcessor* signalProcessor;
};

#endif

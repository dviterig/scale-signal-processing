#include "Scale.h"

#include "MockArduino.h"
#include "constants.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <csv.hpp>

Scale::Scale()
    : _last_read_index(-1), _millis_offset(0)
{
}

// parse_time_to_millis converts an ISO 8601 formatted timestamp to milliseconds since EPOCH
long parse_time_to_millis(const std::string &time_str)
{
    std::tm t = {};
    std::istringstream ss(time_str);
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");

    if (ss.fail())
    {
        throw std::runtime_error("Failed to parse time");
    }

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&t));

    // Parse milliseconds separately
    size_t dotPos = time_str.find('.');
    int milliseconds = 0;
    if (dotPos != std::string::npos)
    {
        milliseconds = std::stoi(time_str.substr(dotPos + 1));
    }

    tp += std::chrono::milliseconds(milliseconds);
    auto duration = tp.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void Scale::begin()
{
    // Read and store all the weight records from the data CSV file

    // Create a CSV reader object
    csv::CSVReader reader(CSV_DATA_PATH);

    // Iterate over the rows in the CSV file
    long first_ts = -1;
    for (csv::CSVRow &row : reader)
    {
        std::string ts = row["ts"].get<std::string>();
        float weight = row["weight"].get<float>();

        long parsed_ts = parse_time_to_millis(ts);
        if (first_ts == -1)
        {
            first_ts = parsed_ts;
        }

        _weight_items.push_back(WeightItem{
            time_diff : parsed_ts - first_ts,
            weight : weight,
        });
    }
}

bool Scale::hasReading()
{
    // We only produce a reading if the time the current session has been running
    // (according to millis()) surpasses the time difference of the weight record (time
    // difference is the relative amount of milliseconds for this record vs the first
    // record.)

    bool has_reading = false;

    // First reading
    if (_last_read_index == -1)
    {
        has_reading = true;
    }
    // This is a special case where no next reading is available, we just return true,
    // because getReading will take care of the wrap around
    else if (_last_read_index + 1 == _weight_items.size())
    {
        has_reading = true;
    }
    else if (millis() - _millis_offset > _weight_items[_last_read_index + 1].time_diff / SPEEDUP_FACTOR)
    {
        has_reading = true;
    }

    return has_reading;
}

float Scale::getReading()
{
    if (!hasReading())
    {
        return 0;
    }

    // Move to the next weight item (wrap-around if we move beyond the last item
    _last_read_index++;
    if (_last_read_index == _weight_items.size())
    {
        std::cout << "Wrapping around..." << std::endl;
        _millis_offset += _weight_items[_last_read_index - 1].time_diff / SPEEDUP_FACTOR;
        _last_read_index = 0;
    }

    return _weight_items[_last_read_index].weight;
}

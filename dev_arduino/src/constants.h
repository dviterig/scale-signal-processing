// SPEEDUP_FACTOR defines the factor by which we speed-up receiving the scale readings
// (vs real-time) 
#define SPEEDUP_FACTOR 1

// CSV_DATA_PATH is the location of the CSV containing the (to be simulated) scale
// readings. (We assume the executable to be run from the build subdirectory).
#define CSV_DATA_PATH "../data/data.csv"

// SIMULATE_DELAY_MS is the number of milliseconds by which we delay each loop() call
// to make the simulation output easier to follow.
#define SIMULATE_DELAY_MS 10

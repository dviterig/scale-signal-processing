# Coding Assignment - Scale signal processing

Consider a simple setup where we have a microcontroller connected to a digital scale. The digital
scale will produce readings (where a reading is the total weight in grams) currently on the scale.
For this coding assignment we have implemented a simple mockup environment that simulates some
actual readings from the scale. Currently the implementation does nothing more than print the weight
values. We ask you to complete the implementation according to a set of requirements that are
specified further along in this document

## Set-up of the directory

The following files / directories are important within the project:

* **src** - The directory container the current mock implementation `main.ino` and the `Scale`
  component are important. Other than that this is the directory where your changes and additions
  should be added to.
* **data** - The directory containing the simulated scale readings. This is used as input to the
  simulation and should not be modified.
* **csv-parser** - This is a standard C++ library used for CSV parsing
  (https://github.com/vincentlaucsb/csv-parser). The library is used internally to simulate weight
  readings and other than that is not really relevant to the assignment.

An example row of the data used by the simulation is:

```csv
ts,weight
2024-07-12 05:42:59.462,21886.375
```

The timestamp (ts) indicated the millisecond precision at which the weight was generated. The weight
is the weight in grams. By default the playback of weight readings will be done in real-time, but
the speed at which the replay is done can be adjusted in `src/constants.h`.

## Description of the assignment

The goal of the assignment is to add signal processing to the code to only extract the *interesting*
weight changes out of all weight changes. An interesting weight change is defined as:

* The period in time when the scale goes from stable (no significant weight changes) to fluctuating,
  back to stable for at least 5 seconds.
* The total weight should exceed 20 grams.
* The data collected should be the start timestamp, the start weight, the end timestamp and end
  weight.

Please note that the digital scale is not perfect there is some standard noise / fluctuation that
should be filtered out.

### Requirements
* You can change and add to the code however you like. However, please keep the mocking and
  simulation untouched (there is no direct need to change this.)
* Maintainability and readability is important, structure and write your code as if your working in
  a team and your code also needs to be understood by others.
* Performance is important, assume the code to be running in an environment like a microcontroller
  where resources are limited.
* The `MockArduino.*` files contain mocking for some common Arduino methods, but this is just for a
  bit of context setting. There is no need to strictly implement this coding assignment using pure
  Arduino code or libs, you can just use any C++ lib as long as you can explain how you would
  implement this on a real microcontroller.

#### Requirements for Part 1
* Write your code in such a way that you could extend it to handle multiple different sensors, for instance if you had depth sensor and camera input to account for as well. You don't have to actually account for depth sensors or cameras in the code, but should be able to discuss how you would add in these additional sensors into your setup
* Organize your code in such a way that the implementation for the scale and various signal processing filters are in separate files / classes such that it is easily extensible by other developers.
* Write you code in such a way that you can easily add extra filters to the weight sensor data to account for additional factors/fluctuations in the sensor readings
* The *interesting* weight changes should be printed to the console using the `Serial` print methods.

#### Requirements for Part 2
* There is another file *data_with_extra_drift.csv* in the data/ directory. Building upon your answer from part one see if you can write additional filter(s) that account for the added fluctuations in the readings due to simulated temperature changes
* Even if you are not able to account for the additional drift please write function(s) that make an attempt so you can explain your thought process during our discussion


## Getting started

### Pre-requisites
We assume the following to be available on your system:

* A recent version of CMake
* A build environment with a compiler like GCC or clang

(For example, on a Debian based system the above can be accomplished by running `apt-get install
cmake build-essential`).

### Building and running the application

If we above is satisfied you should be able to get going by running the following from the root of
the repository:

```bash
# Create a build dir
mkdir build
cd build

# Create a build
cmake ..
make

# Run the application
./main
```

If all is well, you should see something like this:

```bash
$ ./main 
Starting...
  received reading: 21886.4
  received reading: 21582.5
  received reading: 21291.1
  received reading: 20981
  received reading: 20712.3
  received reading: 20940.9
  received reading: 21298.9
  received reading: 21132.8
  received reading: 21334.6
  received reading: 21382.1
  received reading: 21184.4
  received reading: 21042.2
  received reading: 20961.6
  received reading: 21002.8
  received reading: 21157.8
  received reading: 21071.2
  received reading: 21234.2
  ...
```

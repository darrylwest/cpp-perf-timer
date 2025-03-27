# PerfTimer

A general-purpose performance timer implemented as a header-only library in C++. This library allows you to measure the execution time of code segments with precision and provides delayed logging capabilities.

## Version

Current version: **0.6.4**

## Features

- High-resolution timing using `std::chrono`
- Easy-to-use interface for starting and stopping timers
- Customizable precision for duration output
- Delayed logging to minimize console output delays

## Installation

Simply include the `perftimer` header file in your project:

```cpp
#include "perftimer.h"

## Usage

### Creating a timer


### Starting the timer


### Stopping the timer


### Getting the Duration


### Showing the Duration


### Logging Comments



## Example

```cpp

#include <perftimer.hpp>
#include <cstdio>
#include <thread>

int main() {
    perftimer::PerfTimer("Example Thing");

    // do some setup things if necessary

    timer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    timer.log << "this is a log statement"
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    timer.stop();

    timer.show_duration();

    // now show any log statements without altering the timing
    std::puts(timer.log.str());

    return 0;
}
```



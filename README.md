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
#include <perftimer/perftimer.hpp>
```

## Usage

### Creating a timer

```cpp
perftimer::PerfTimer timer("My Timer");
```

### Starting the timer

```cpp
timer.start();
```

### Stopping the timer

```cpp
timer.stop();
```

### Getting the Duration

```cpp
auto duration = timer.get_duration();
```

### Showing the Duration

```cpp
timer.show_duration();
```

### Logging Comments

```cpp
timer.log << "this is my log statement.\n";
```

## Example

```cpp

#include <perftimer/perftimer.hpp>
#include <cstdio>
#include <thread>

int main() {
    perftimer::PerfTimer timer("Example Thing");

    // do some setup things if necessary

    timer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    timer.log << "this is a log statement\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    timer.stop();

    timer.show_duration();

    // now show any log statements without altering the timing
    std::puts(timer.log.str().c_str());

    return 0;
}

```

###### 2025-03-26 | dpw

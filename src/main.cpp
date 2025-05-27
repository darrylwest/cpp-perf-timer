
#include <atomic>
#include <chrono>
#include <cstdio>
#include <iomanip>  // For std::fixed and std::setprecision
#include <perftimer/perftimer.hpp>
#include <string>
#include <thread>

using namespace std::chrono;
using namespace std::literals;  // For convenient time literals like 1s

// Global atomic boolean to signal the display thread to stop
std::atomic<bool> running = true;

void display_elapsed_time() {
    auto start_time = high_resolution_clock::now();
    while (running) {
        auto now = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - start_time);
        // Use \r to return the cursor to the beginning of the line for in-place update
        std::cout << "\rElapsed seconds: " << float(elapsed.count()) / 1000.0 << std::flush;
        std::this_thread::sleep_for(0.1s);  // Update every second
    }
    std::cout << "\rElapsed time display stopped.        \n";  // Clear the last output
}

int main() {
    perftimer::PerfTimer timer("Stopwatch Timer");

    std::cout << "Press Enter to stop the timer\n";

    timer.start();

    std::thread display_thread(display_elapsed_time);

    std::string line;
    std::getline(std::cin, line);

    running = false;
    timer.stop();

    display_thread.join();

    std::cout << timer.get_name() << " duration: " << std::setprecision(6) << timer.get_seconds() << " seconds.\n";

    return 0;
}

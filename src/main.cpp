
#include <atomic>
#include <chrono>
#include <cstdio>
#include <iomanip>  // For std::fixed and std::setprecision
#include <perftimer/perftimer.hpp>
#include <string>
#include <thread>
#include <vendor/ansi_colors.hpp>

using namespace std::chrono;
using namespace std::literals;  // For convenient time literals like 1s
using namespace colors;

// Global atomic boolean to signal the display thread to stop
std::atomic<bool> running = true;

constexpr std::string_view help_text = R"(
Usage: perf-timer [run executable|help]

  executable:  start the timer and run the executable; report the time when complete.
  help      :   show this help file.

With no args the timer starts on the console.

Example Use: perf-timer find ./ -type f -print

)";

void show_help() {
    std::cout << green << "Version: " << perftimer::VERSION << reset << '\n';
    std::cout << yellow << help_text << reset << '\n';
}

void display_elapsed_time() {
    auto start_time = high_resolution_clock::now();
    while (running) {
        auto now = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - start_time);
        // Use \r to return the cursor to the beginning of the line for in-place update
        std::cout << green << "\rElapsed seconds: " << float(elapsed.count()) / 1000.0 << reset
                  << std::flush;
        std::this_thread::sleep_for(0.1s);  // Update every second
    }
    std::cout << yellow << "\rElapsed time display stopped.\n"
              << reset << '\n';  // Clear the last output
}

int main(int argc, char *argv[]) {
    perftimer::PerfTimer timer("perf");

    if (argc > 1) {
        if (argv[1] == std::string_view("help") || argv[1] == std::string_view("--help")) {
            show_help();
            return 0;
        }
        std::string cmd = argv[1];
        if (argc > 2) {
            for (auto i = 2; i < argc; i++) {
                cmd.append(" ").append(argv[i]);
            }
        }

        std::cout << bright::cyan << cmd << reset << "\n\n";
        timer.start();
        std::system(cmd.c_str());
        timer.stop();
        std::cout << '\n'
                  << bright::cyan << "--------------- " << cmd << " completed..." << reset << '\n';
        timer.show_duration();

    } else {
        std::cout << "Press Enter to stop the timer\n";

        timer.start();

        std::thread display_thread(display_elapsed_time);

        std::string line;
        std::getline(std::cin, line);

        running = false;
        timer.stop();

        display_thread.join();
    }

    std::cout << timer.get_name() << ": duration: " << std::setprecision(6) << timer.get_seconds()
              << " seconds.\n";

    return 0;
}

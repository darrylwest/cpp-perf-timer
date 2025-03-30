
#include <cstdio>
#include <perftimer/perftimer.hpp>
#include <thread>

int main() {
    perftimer::PerfTimer timer("Example Thing");

    // do some setup things if necessary

    timer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    timer.log << "this is a log statement\n";
    timer.stop();
    timer.log << "stop 1 after 500 ms\n";

    std::string duration_string = timer.get_duration_string(": 1/2 way test: ");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    timer.log << "stop 2 after 1,000 ms\n";

    timer.stop();

    std::cout << duration_string << '\n';

    timer.show_duration(": multiple stops, 1 start: ");

    // now show any log statements without altering the timing
    std::puts("Now show the log statements:");
    std::puts(timer.log.str().c_str());

    return 0;
}

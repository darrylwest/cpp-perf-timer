
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



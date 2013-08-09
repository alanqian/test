#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    cout << "hello clock!" << endl;
    auto x = hours(3);
    auto y = hours(3) + minutes(31) + seconds(4);
    auto t = system_clock::now();
    // do something
    microseconds d = monotonic_clock::now() - t; // we want the result in nanoseconds
    int64_t usec = static_cast<int64_t> (d);
    return 0;
}

#include "../headers/Time.h"

Time::Time(std::chrono::steady_clock::time_point s) : start(s)
{
    std::cout << "The countdown has begun!\n";
}

// Function to calculate elapsed time in seconds
[[nodiscard]] long long Time::elapsed(std::chrono::steady_clock::time_point moment) const
{
    return std::chrono::duration_cast<std::chrono::seconds>(moment - start).count();
}

// Overloading the << operator to print elapsed time
std::ostream& operator<<(std::ostream& os, const Time& t)
{
    auto duration = std::chrono::steady_clock::now() - t.start;
    os << "Elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(duration).count() << " seconds";
    return os;
}

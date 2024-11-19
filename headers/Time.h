#ifndef TIME_H
#define TIME_H
#include <chrono>
#include <iostream>

class Time
{
    std::chrono::steady_clock::time_point start;

public:
    // Constructor declaration with default argument in the header file
    explicit Time(std::chrono::steady_clock::time_point s = std::chrono::steady_clock::now());

    // Function to get the elapsed time in seconds
    [[nodiscard]] long long elapsed(std::chrono::steady_clock::time_point moment) const;

    // Overloading the << operator to print the elapsed time in a user-friendly format
    friend std::ostream& operator<<(std::ostream& os, const Time& t);
};

#endif // TIME_H

#ifndef TIMER_H
#define TIMER_H

#include<chrono>

class Timer
{
public:
    Timer();
    ~Timer() = default;
    long time_passed_milli();
    void reset();
    void start();
private:
    std::chrono::time_point<std::chrono::system_clock> _start;
};



#endif // TIMER_H
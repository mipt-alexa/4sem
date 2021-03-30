#include <chrono>
 #include <iostream>

class Timer{
public:
    using clock_t = std::chrono::steady_clock;
    using timepoint_t = clock_t::time_point ;
    Timer() {
        m_begin = clock_t::now();
        last_timestamp = clock_t::now();
        time = std::chrono::milliseconds (0);
    }
    ~Timer(){
        auto end = clock_t::now();
    }

    void stop(){
        auto current = clock_t::now();
        time = std::chrono::duration_cast <std::chrono::milliseconds>(current - last_timestamp);
        std::cout << time.count() << " ms\n";
    }

    void run(){
        last_timestamp = clock_t::now();
        //std::cout << "timer is on\n";
    }

private:
    timepoint_t  m_begin;
    timepoint_t last_timestamp;
    std::chrono::milliseconds time;
};

#ifndef CPP_4SEM_TIMER_H
#define CPP_4SEM_TIMER_H

#endif //CPP_4SEM_TIMER_H

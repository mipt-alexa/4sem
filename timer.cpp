
#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>

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
        std::cout <<  "total time is " <<
                  std::chrono::duration_cast <std::chrono::seconds > (end - m_begin).count()
                  <<  "seconds\n" ;
    }

    void stop(){
        auto current = clock_t::now();
        time += std::chrono::duration_cast <std::chrono::milliseconds>(current - last_timestamp);
        std::cout << "stop, " << time.count() <<   " millisecond(s) passed\n";
    }

    void run(){
        last_timestamp = clock_t::now();
        std::cout << "timer is on\n";
    }

private:
    timepoint_t  m_begin;
    timepoint_t last_timestamp;
    std::chrono::milliseconds time;
};

int main(){

    Timer t;
    int a = 1;
    while (a != 0) {        // 1 for stop, 2 for start
        std::cin >> a;
        if (a == 1)
            t.stop();
        if (a == 2)
            t.run();
    }

    return 0;
}

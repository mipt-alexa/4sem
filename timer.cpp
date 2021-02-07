
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
    }
    ~Timer(){
        auto end = clock_t::now();
        std::cout <<  "total time is " <<
                  std::chrono::duration_cast <std::chrono::milliseconds > (end - m_begin).count()
                  <<  " milliseconds\n" ;
    }

    void stop(){             // prints the duration using the current epoch (since the last restart)
        auto current = clock_t::now();
        std::cout <<
                  std::chrono::duration_cast <std::chrono::seconds > (current - last_timestamp).count()
                  <<   " second(s) passed\n";
    }

    void restart(){         // sets up a new epoch
        last_timestamp = clock_t::now();
        std::cout << "timer is restarted\n";
    }

private:
    timepoint_t  m_begin;
    timepoint_t last_timestamp;
};

int main(){

    Timer t;
    int a = 1;
    while (a != 0) {
        std::cin >> a;
        if (a == 1)
            t.stop();
        if (a == 2)
            t.restart();
    }

    return 0;
}

 #include <vector>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
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
        std::cout << time.count() <<   " millisecond(s)\n";
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


const unsigned int n = 100000;


int main(){

    std::vector<double> vec(n);
    std::array<double, n> arr;
    std::list<double> list;
    std::forward_list<double> fl;
    std::deque<double> deq;

    for (int i = 0; i < n; ++i) {
        double val = i * (n - i);
        vec[i] = val;
        arr[i] = val;
        list.push_back(val);
        fl.push_front(val);
        deq.push_back(val);
    }

    Timer t;

    std::cout << "SORTING \n\n";


    std::cout << "list takes ";
    t.run();
    list.sort();
    t.stop();
    std::cout << "\n";

    std::cout << "forward list takes ";
    t.run();
    fl.sort();
    t.stop();
    std::cout << "\n";

    std::cout << "deque with std::sort takes ";
    t.run();
    std::sort(std::begin(deq), std::end(deq));
    t.stop();
    std::cout << "\n";

    std::cout << "vector with std::sort takes ";
    t.run();
    std::sort(vec.begin(), vec.end());
    t.stop();
    std::cout << "\n";

    std::cout << "array with std::sort takes ";
    t.run();
    std::sort(std::begin(arr), std::end(arr));
    t.stop();
    std::cout << "\n";


    // RESULTS  [milliseconds]:
    //
    // list            22  23  23
    // forward list    31  26  22
    // vector          44  70  42
    // array           64  65  63
    // deque          317 349 355


    return 0;
}


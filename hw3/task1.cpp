#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

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

    void stop(std::ofstream& ofstream){
        auto current = clock_t::now();
        time = std::chrono::duration_cast <std::chrono::milliseconds>(current - last_timestamp);
        ofstream << time.count() << " ";
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


int main(){

    Timer t;

    std::ofstream txt_file;
    txt_file.open(R"(C:\Users\User\cpp_4sem\hw3\mydata.txt)");

    std::vector<unsigned int> sizes(25);
    sizes[0] = 10000;

    int i;
    for (i = 1; i < 10; ++i) {
        sizes[i] = 1.5*sizes[i-1];
    }
    for (; i < sizes.size(); ++i) {
        sizes[i] = 1.15*sizes[i-1];
    }

    std::set<int> set;
    std::vector<int> vec;

    for (auto j : sizes) {
        vec.reserve(j);
        txt_file << j << " ";

        for (int i = 0; i < j; ++i) {
            vec.push_back(j - i);
        }

        t.run();
        for (int i = 0; i < j; ++i) {
            set.insert(j - i);
        }
        t.stop(txt_file);

        t.run();
        std::sort(vec.begin(), vec.end());
        t.stop(txt_file);

        txt_file << std::endl;

        vec.clear();
        set.clear();
    }


}
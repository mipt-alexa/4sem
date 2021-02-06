//
 
#include<iostream>
#include<chrono> //интервалы и моменты
#include<vector>
#include<algorithm>

class Timer{
public:
    using clock_t = std::chrono::steady_clock;
    using timepoint_t = clock_t ::time_point ;
    Timer() : m_begin(clock_t::now()) {}
    ~Timer(){
        auto end = clock_t::now();
        std::cout <<  "milliseconds: " <<
        std::chrono::duration_cast <std::chrono::milliseconds > (end - m_begin).count() ;

void f(){}

int main(){

    std::cout<<"j";
    //hello from master

    return 0;
}
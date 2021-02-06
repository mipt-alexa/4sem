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

    }

private:
    timepoint_t  m_begin;
};

int main(){

    // std::ratio <1, 3> r;

    // интервал -- n тактов заданной продолжительности
    // timepoint - комбинация интервала и эпохи
    // эпоха - начало отсчёта
    // clock - опр эпоху и мин такт

    //std::chrono::duration<int, std::ratio<1, 1>> a(42);
    //std::chrono::duration<double, std::ratio<60>> b(0.5);

    std::chrono::seconds a(20);
    std::chrono::hours b(2);
    std::chrono::microseconds c(42);

    c += a+b;
    --c;
    c *= 2;

    std::cout << c.count() << "\n";

    // system_clock - OS
    // staedy_clock - не допускают подведения
    // high_resolution_clock - с мин доступным тактом

    std::vector v(100000, 0);
    for (auto i = 0U; i<std::size(v); ++i) {
        v[i] = 1000U - i;
    }

    Timer t;
    std::sort(std::begin(v), std::end(v));

    return 0;
}
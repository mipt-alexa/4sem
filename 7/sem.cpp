#include <thread>
#include <iostream>
#include <future>

#include "boost/asio.hpp"

void f(){

    std::cout <<"mi";
}

int main(){

//    std::thread t(f);
////    t.join();
////    t.detach();
//
//    std::cout << std::thread::hardware_concurrency();


//    std::future<int> f = std::async([](int x) {return  x+1;}, 42);
//
//    std::cout << f.get() << std::endl; // wait valid

    //get только один раз

//    std::future<void> f = std::async([]() {throw std::logic_error("g");});
//
//    try{
//        f.get();
//    } catch(std::exception &e) {
//        std::cerr<< e.what();
//    }

//    std::packaged_task<int()> task([]() {return 42;});

//    auto result = task.get_future();
//
//    std::thread(std::move(task)).detach();

    boost::asio::thread_pool tp(64);

    std::packaged_task<int()> task([]() {return 42;});

    auto result = boost::asio::post(tp, std::move(task));

    std::cout <<result.get();

}
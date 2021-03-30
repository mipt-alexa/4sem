#include <iostream>
#include <vector>
#include "Timer.h"
#include <random>
#include <thread>
#include <atomic>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/stack.hpp.>
#include "threadsafe_stack.hpp"
#include "threadsafe_queue.hpp"


template<typename Container>
void push_many(Container& container, std::size_t n, std::atomic< bool >& flag){

    while (!flag.load()){
        std::this_thread::yield();
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution< int > dis(-10000, 10000);

    for (int i = 0; i < n; ++i) {
        container.push(dis(gen));
    }

}


template<typename Container>
 void pop_many(Container& container, std::size_t n, std::atomic< bool >& flag){

    while (!flag.load()){
        std::this_thread::yield();
    }

    int a;
    for (int i = 0; i < n; ++i) {
        container.pop(a);
    }

}



void Stack_Test(const std::size_t num_threads, const std::size_t num_elements){

    std::cout << "STACK TEST:  N = " << num_threads << ", M = " << num_elements << "\n";

    Timer t;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution< int > dis(-10000, 10000);

    Threadsafe_Stack< int > my_stack;
    boost::lockfree::stack< int > boost_stack(num_threads*num_elements);


    for (int i = 0; i < num_threads*num_elements; ++i) {  //заполняем чтобы не выбрасывало исключение при попытке сделать pop с пустым стеком

        my_stack.push(dis(gen));
        boost_stack.push(dis(gen));

    }

    std::vector< std::thread > threads(2*num_threads);

    std::atomic< bool > flag = false;

    int i;
    for (i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(push_many< Threadsafe_Stack< int >>, std::ref(my_stack),
                                 num_elements, std::ref(flag));
    }

    for (; i < 2*num_threads; ++i) {
        threads[i] = std::thread(pop_many< Threadsafe_Stack< int >>, std::ref(my_stack),
                                 num_elements, std::ref(flag));
    }


    std::cout << "my stack   ";

    t.run();
    flag = true;

    for (auto & thread : threads) {
        thread.join();
    }

    t.stop();


    flag = false;

    for (i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(push_many< boost::lockfree::stack < int >>, std::ref(boost_stack),
                                 num_elements, std::ref(flag));
    }

    for (; i < 2*num_threads; ++i) {
        threads[i] = std::thread(pop_many< boost::lockfree::stack < int >>, std::ref(boost_stack),
                                 num_elements, std::ref(flag));
    }

    std::cout << "boost stack   ";

    t.run();
    flag = true;

    for (auto & thread : threads) {
        thread.join();
    }

    t.stop();
    std::cout << "\n";

}


void Queue_Test(const std::size_t num_threads, const std::size_t num_elements){

    std::cout << "QUEUE TEST:  N = " << num_threads << ", M = " << num_elements << "\n";

    Timer t;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution< int > dis(-10000, 10000);

    Threadsafe_Queue< int > my_queue;
    boost::lockfree::queue< int > boost_queue(num_threads*num_elements);


    for (int i = 0; i < num_threads*num_elements; ++i) {  //заполняем чтобы не выбрасывало исключение при попытке сделать pop с пустой очередью

        my_queue.push(dis(gen));
        boost_queue.push(dis(gen));

    }

    std::vector< std::thread > threads(2*num_threads);

    std::atomic< bool > flag = false;

    int i;
    for (i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(push_many< Threadsafe_Queue < int >>, std::ref(my_queue), num_elements, std::ref(flag));
    }

    for (; i < 2*num_threads; ++i) {
        threads[i] = std::thread(pop_many< Threadsafe_Queue < int >>, std::ref(my_queue), num_elements, std::ref(flag));
    }


    std::cout << "my q ";

    t.run();
    flag = true;

    for (auto & thread : threads) {
        thread.join();
    }

    t.stop();


    flag = false;

    for (i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(push_many< boost::lockfree::queue < int >>, std::ref(boost_queue), num_elements, std::ref(flag));
    }

    for (; i < 2*num_threads; ++i) {
        threads[i] = std::thread(pop_many< boost::lockfree::queue < int >>, std::ref(boost_queue), num_elements, std::ref(flag));
    }

    std::cout << "boost q  ";

    t.run();
    flag = true;

    for (auto & thread : threads) {
        thread.join();
    }

    t.stop();
    std::cout << "\n";

}


int main(){

    const std::size_t n = std::thread::hardware_concurrency();
    const std::size_t m = 100000;

    Stack_Test(n, 10);
    Stack_Test(n, 5);
    Stack_Test(n, 2*m);

    Queue_Test(n, 10);
    Queue_Test(n, 5);
    Queue_Test(n, 10*m);


    //results:
//
//    STACK TEST:  N = 4, M = 100000
//    my stack   334 ms
//    boost stack   200 ms
//
//    STACK TEST:  N = 8, M = 100000
//    my stack   711 ms
//    boost stack   426 ms
//
//    STACK TEST:  N = 4, M = 200000
//    my stack   684 ms
//    boost stack   403 ms
//
//    QUEUE TEST:  N = 4, M = 100000
//    my q 355 ms
//    boost q  274 ms
//
//    QUEUE TEST:  N = 8, M = 100000
//    my q 722 ms
//    boost q  592 ms
//
//    QUEUE TEST:  N = 4, M = 2000000
//    my q 6943 ms
//    boost q  5024 ms
//
//    буст быстрее

}

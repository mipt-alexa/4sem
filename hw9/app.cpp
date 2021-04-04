#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <chrono>

#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/containers/vector.hpp"
#include <boost/interprocess/containers/string.hpp>
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/sync/interprocess_condition.hpp"


using namespace boost::interprocess;


using char_alloc = allocator < char, managed_shared_memory::segment_manager >;
using str = basic_string< char, std::char_traits<char>, char_alloc>;

using vec_alloc = allocator < str, managed_shared_memory::segment_manager>;
using vector_str = vector < str, vec_alloc >;



void print(interprocess_mutex *mutex, interprocess_condition *cv, vector_str *v, bool& flag){


    std::cout << v->size() << " messages in memory\n";

    std::unique_lock lock1(*mutex);

    for(auto & i : *v) {

        std::cout << i.data() << "\n";
    }

    lock1.unlock();

    std::cout << "print of message history finished \n";

    while(true){

        std::unique_lock lock2(*mutex);

        cv->wait(lock2);

        if (flag){

            std::cout << "shutting down printing...\n" ;  // so i can check if this thread has stopped

            break;
        }

        if(!v->empty()) {
            std::cout << v->back().data() << "\n";
        }
    }

}


void read(interprocess_mutex *mutex, interprocess_condition *cv,  vector_str *v, str &str1, bool& flag){

    while (true) {
        std::string read;

        std::getline(std::cin, read);

        if (read == "exit") {

            cv->notify_all();   // so printing thread could stop

            flag = true;

            std::cout << "shutting down reading...\n";     // so i can check whether shutdown is emergency or not
            std::this_thread::sleep_for(std::chrono::seconds(1));

            break;
        }

        std::scoped_lock lock1(*mutex);

        for (char &c : read) {
            str1.push_back(c);
        }

        v->push_back(str1);

        cv->notify_all();

        str1.erase();
    }

}


int main(){

    const std::string mem_name = "shared memory";

    shared_memory_object::remove(mem_name.c_str());

    system("pause");

    managed_shared_memory shared_mem(open_or_create, mem_name.c_str(), 50000U);


    auto cv = shared_mem.find_or_construct< interprocess_condition >("cv")();
    auto mutex = shared_mem.find_or_construct< interprocess_mutex >("mutex")();


    auto v = shared_mem.find_or_construct< vector_str >("v")(shared_mem.get_segment_manager());

    str str1(shared_mem.get_segment_manager());


    bool exit = false;

    std::thread printing = std::thread(print, mutex, cv, v, std::ref(exit));

    printing.detach();

    std::thread reading = std::thread(read, mutex, cv, v, std::ref(str1), std::ref(exit));

    reading.join();

}


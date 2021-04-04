#include <iostream>
#include <mutex>
#include <string>

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



int main(){

    system("pause");

    const std::string mem_name = "shared memory";

    shared_memory_object::remove(mem_name.c_str());

    managed_shared_memory shared_mem(create_only, mem_name.c_str(), 4090U);


    auto mutex = shared_mem.construct< interprocess_mutex >("mutex")();
    auto cv = shared_mem.construct< interprocess_condition >("cv")();


    auto v = shared_mem.construct< vector_str >("v")(shared_mem.get_segment_manager());
//    auto str1 = shared_mem.construct< str >("str")(shared_mem.get_segment_manager());

    str str1(shared_mem.get_segment_manager());

    std::string buffer;

    do{
        std::getline(std::cin, buffer);

        std::scoped_lock lock(*mutex);

        for(char& c : buffer) {

            str1.push_back(c);
        }

        v->push_back(str1);

        cv->notify_all();


    } while (buffer != "exit");


    shared_memory_object::remove(mem_name.c_str());

}


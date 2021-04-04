#include <iostream>
#include <mutex>

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

    const std::string n = "shared memory";

    managed_shared_memory shared_mem(open_only, n.c_str());


    auto mutex = shared_mem.find< interprocess_mutex>("mutex").first;
    auto cv = shared_mem.find< interprocess_condition>("cv").first;


    auto v = shared_mem.find< vector_str >("v").first;

    std::string read;

    do{

        std::unique_lock lock(*mutex);
        cv->wait(lock);

        std::cout << v->back().data() << "\n";

        std::getline(std::cin, read);

//        v->pop_back();


    } while (read != "exit");



}

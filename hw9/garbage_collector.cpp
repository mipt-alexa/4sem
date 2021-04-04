#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "boost/interprocess/managed_shared_memory.hpp"

using namespace boost::interprocess;


int main() {

    const std::string mem_name = "shared memory";

    shared_memory_object::remove(mem_name.c_str());

    std::cout << "memory cleaned";


}

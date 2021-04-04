#include <iostream>
#include <mutex>

#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/containers/vector.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/sync/interprocess_condition.hpp"
#include "boost/interprocess/sync/interprocess_mutex.hpp"

int main(){

    system("pause");

    const std::string n = "sm";

    boost::interprocess::shared_memory_object::remove(n.c_str());

    boost::interprocess::managed_shared_memory sm(boost::interprocess::create_only,
                                                 n.c_str(), 4090U);


    using allocator_t = boost::interprocess::allocator <int,
    boost::interprocess::managed_shared_memory::segment_manager >;

    using vector_t = boost::interprocess::vector < int, allocator_t >;

    auto v = sm.construct< vector_t >("v")(sm.get_segment_manager());

    auto m = sm.construct< boost::interprocess::interprocess_mutex>("m")();

    auto c = sm.construct< boost::interprocess::interprocess_condition>("c")();

    int x;

    do{
        std::cin >>x;

        std::scoped_lock lock(*m);

        v->push_back(x);

        c->notify_one();


    } while (x != 0);


    boost::interprocess::shared_memory_object::remove(n.c_str());

}

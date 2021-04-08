#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <mutex>
#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

int main(int argc, char ** argv)
{
	const std::string shared_memory_name = "managed_shared_memory";

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);

	auto i = shared_memory.find_or_construct < int > ("Integer")(0);

	const std::string mutex_name = "mutex";
	const std::string condition_name = "condition";

	auto mutex =
		shared_memory.find_or_construct < boost::interprocess::interprocess_mutex > (mutex_name.c_str())();
	auto condition =
		shared_memory.find_or_construct < boost::interprocess::interprocess_condition > (condition_name.c_str())();

	{
		std::unique_lock < boost::interprocess::interprocess_mutex > lock(*mutex);

		condition->notify_one();
		condition->notify_all();

		condition->wait(lock, []() { return true; });
	}

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}
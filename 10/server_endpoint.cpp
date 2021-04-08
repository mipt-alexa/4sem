#include <iostream>

#include <boost/asio.hpp>

int main(int argc, char ** argv)
{
	auto port = 3333;

	boost::asio::ip::address ip_address = 
		boost::asio::ip::address_v6::any();

	boost::asio::ip::tcp::endpoint endpoint(ip_address, port);

	std::cout << "Endpoint ready" << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}
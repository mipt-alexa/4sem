#include <iostream>

#include <boost/asio.hpp>

int main(int argc, char ** argv)
{
	auto port = 3333;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

	boost::asio::io_service io_service;

	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

	acceptor.bind(endpoint);

	std::cout << "Acceptor binded" << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}
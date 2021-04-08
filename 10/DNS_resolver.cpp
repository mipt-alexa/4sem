#include <iostream>

#include <boost/asio.hpp>

int main(int argc, char ** argv)
{
	std::string host = "yandex.ru";
	std::string port = "3333";

	boost::asio::io_service io_service;

	boost::asio::ip::tcp::resolver::query resolver_query(host,
		port, boost::asio::ip::tcp::resolver::query::numeric_service);

	boost::asio::ip::tcp::resolver resolver(io_service);

	boost::asio::ip::tcp::resolver::iterator iterator =
		resolver.resolve(resolver_query);

	boost::asio::ip::tcp::resolver::iterator iterator_end;

	for (; iterator != iterator_end; ++iterator) 
	{
		boost::asio::ip::tcp::endpoint endpoint = iterator->endpoint();

		std::cout << endpoint.address().to_string() << std::endl;
	}

	system("pause");

	return EXIT_SUCCESS;
}
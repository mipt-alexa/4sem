#include <iostream>

#include <boost/asio.hpp>

int main(int argc, char ** argv)
{ 
	boost::asio::io_service ios;

	boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v4();

	try 
	{
		boost::asio::ip::tcp::socket socket(ios, protocol);
	}
	catch (boost::system::system_error & e) 
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
	}

	std::cout << "Socket ready" << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}
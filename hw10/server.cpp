#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "soket_data_transfer.h"


int main(int argc, char ** argv)
{
    system("chcp 1251");

    const std::size_t size = 30;

    auto port = 3333;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

    boost::asio::io_service io_service;

    std::string buffer;

    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

    acceptor.bind(endpoint);
    acceptor.listen(size);

    boost::asio::ip::tcp::socket socket1(io_service);

    acceptor.accept(socket1);

    std::cout << "successfully connected\n";

    std::string my_name;
    std::cout << "What's your name?\n";

    std::getline(std::cin, my_name);

    std::thread printing = std::thread(print, std::ref(socket1));

    std::thread writing = std::thread(write, std::ref(socket1), std::ref(my_name));

    printing.detach();
    writing.join();


    return EXIT_SUCCESS;
}

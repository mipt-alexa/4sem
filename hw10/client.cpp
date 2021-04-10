#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include "soket_data_transfer.h"


int main(int argc, char ** argv)
{
    system("chcp 1251");

    std::string raw_ip_address = "127.0.0.1";

    auto port = 3333;

    boost::asio::ip::tcp::endpoint endpoint(
            boost::asio::ip::address::from_string(raw_ip_address), port);

    boost::asio::io_service io_service;

    boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());

    socket.connect(endpoint);

    std::cout << "successfully connected\n";

    std::string my_name;
    std::cout << "What's your name?\n";

    std::getline(std::cin, my_name);

    std::thread printing = std::thread(print, std::ref(socket));

    std::thread writing = std::thread(write, std::ref(socket), std::ref(my_name));

    printing.detach();
    writing.join();

    system("pause");

    return EXIT_SUCCESS;
}
#include <iostream>
#include <thread>

#include <boost/asio.hpp>

void write_data(boost::asio::ip::tcp::socket & socket, std::string &name)
{
    std::string data;

    std::getline(std::cin, data);

    data = name + ": " + data + "\n";

    boost::asio::write(socket, boost::asio::buffer(data));
}


void write(boost::asio::ip::tcp::socket &socket, std::string &name){
    do {
        try {

            write_data(socket, name);
        }
        catch (boost::system::system_error &e) {
            std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

            system("pause");

            std::cout << e.code().value();
        }
    } while (true);

}


std::string read_data_until(boost::asio::ip::tcp::socket & socket)
{
    boost::asio::streambuf buffer;

    boost::asio::read_until(socket, buffer, '\n');

    std::string message;

    // Because buffer 'buf' may contain some other data
    // after '\n' symbol, we have to parse the buffer and
    // extract only symbols before the delimiter.
    std::istream input_stream(&buffer);
    std::getline(input_stream, message, '\n');

    return message;
}


void print(boost::asio::ip::tcp::socket &socket1){
    std::string buffer;

    do {
        try {

            buffer = read_data_until(socket1);

            std::cout << buffer << std::endl;
        }
        catch (boost::system::system_error &e) {
            std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

            system("pause");

            std::cout <<  e.code().value();
        }

    } while (true);
}
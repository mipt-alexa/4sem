#include <iostream>
#include <regex>

int main() {

    std::string date_data = "00.00.0000 11.11.1111 99.01.2000 1.11.2000 01.11.2000 33.03.3333 12.12.2012";
    std::cout << date_data << std::endl << std::endl;

    std::string time_data = "11:11:11 10:01:00 00:00:00 23:59:59 24:00:00 23:59:60";
    std::cout << time_data << std::endl << std::endl;

    std::regex date_pattern(R"( (0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.]\d{4})");
    std::regex time_pattern(R"( (0[0-9]|1[0-9]|2[0-3])[- :]([0-5][0-9])[- :]([0-5][0-9]))");

    std::sregex_iterator begin1(date_data.cbegin(), date_data.cend(), date_pattern);
    std::sregex_iterator begin2(time_data.cbegin(), time_data.cend(), time_pattern);
    std::sregex_iterator end;


    std::for_each(begin1, end, [](const std::smatch & matches)
    {
        std::cout << matches[0] << std::endl;
    });

    std::for_each(begin2, end, [](const std::smatch & matches)
    {
        std::cout << matches[0] << std::endl;
    });


//    RESULT:
//
//    11.11.1111
//    01.11.2000
//    12.12.2012
//    10:01:00
//    00:00:00
//    23:59:59

    return 0;
}
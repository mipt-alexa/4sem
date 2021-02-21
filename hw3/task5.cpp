#include <iostream>
#include <string>
#include <iomanip>


#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;

struct Record
{
    std::string name;
    int number;
    int postcode;
};

using phone_book_multi_index = multi_index_container <
        Record, indexed_by <
                hashed_non_unique <
                        member < Record, std::string, &Record::name > > ,

                random_access <  //vector
                               >,

		        ordered_non_unique <  // multiset
		            	member < Record, std::string , &Record::name > > > > ;

int main(int argc, char ** argv)
{
    phone_book_multi_index book;

    book.insert({ "Cat",  1111, 11000 });
    book.insert({ "Shark",  3333, 11533 });
    book.insert({ "Raven",  6666, 11533 });
    book.insert({ "Dog",  1221, 11043 });

    const auto & book_hash = book.get<0>();
    const auto & book_vector = book.get < 1 > ();
    const auto & book_multiset = book.get< 2 >();

    std::cout << "1. The phone book layout for print:\n\n";
    std::cout << std::setw(8) << std::left << "Name" <<
              std::setw(8) << std::right << "Number" <<
              std::setw(9) << std::right << "Postcode"<< std::endl;

    for (const auto & i : book_multiset){
        std::cout << std::setw(8) << std::left << i.name <<
        std::setw(8) << std::right << i.number <<
        std::setw(8) << std::right << i.postcode << std::endl;
    }

    std::cout << "\n2. Advertising agency:\n";

    std::cout << "Want to call half of city's residents\n";

    unsigned int n = book_vector.size();  //city population

    for (int i = n/2; i < n; ++i) {
        std::cout << "calling " << book_vector[i].name << " by phone number " << book_vector[i].number << "...\n";
    }

    std::cout << "\n3. Regular user wants to find their friend's number:\n";

    std::string name_to_search;
    std::cin >> name_to_search;
    auto it = book_hash.find(name_to_search);
    if (it != book_hash.end())
        std::cout << it->name << " 's phone number is " << it->number << "\n";
    else
        std::cout << name_to_search << " wasn't found in the phone book..";

    return 0;
}
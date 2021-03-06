#include <iostream>
#include <regex>

int main() {

    std::string data = "a@a.a aa_a@aa.e a-a-a@r.e asjfh askbf \n @r.r vr@ vfn@bf bng@b b_b_b@a.a.a 543 7529@r1.r \n "
                       "13@.12 13@a.12 13@a.a example@s.example \n user--1@example.org @@Abc.example.com "
                       " @@ a'a@a.r a*a-a!11?a@a-a.ru  ex@ex!x.r";
    std::cout << data << std::endl << std::endl;

    std::regex pattern(R"(\w+([!#$%&'*+-/=?^_`{|}~]\w+)*@(\w+(-\w+)*\.[[:alpha:]]{1,}))");

    std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
    std::sregex_iterator end;

    std::cout << "address and domain: " << std::endl << std::endl;

    std::for_each(begin, end, [](const std::smatch & matches)
    {
        std::cout << matches[0] << " | " << matches[2] << std::endl;
    });


//    RESULT:
//
//    address and domain:
//
//    a@a.a | a.a
//    aa_a@aa.e | aa.e
//    a-a-a@r.e | r.e
//    b_b_b@a.a | a.a
//    7529@r1.r | r1.r
//    13@a.a | a.a
//    example@s.example | s.example
//    1@example.org | example.org
//    a'a@a.r | a.r
//    a*a-a!11?a@a-a.ru | a-a.ru


    return 0;
}
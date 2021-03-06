#include <iostream>
#include <boost/locale.hpp>
#include <fstream>


std::string convert_locale_to_utf(const std::string & string)
{
    boost::locale::generator generator;
    generator.locale_cache_enabled(true);

    std::locale locale =
            generator(boost::locale::util::get_system_locale());

    return boost::locale::conv::to_utf < char >(string, locale);
}

std::string convert_utf_to_locale(const std::string & string)
{
    boost::locale::generator generator;
    generator.locale_cache_enabled(true);

    std::locale locale =
            generator(boost::locale::util::get_system_locale());

    return boost::locale::conv::from_utf < char >(string, locale);
}


int main(){
    system("chcp 1251");

    std::unordered_map<std::u32string, std::u32string> romanized_script;

    std::ifstream txt_file;
    txt_file.open("../hw5/romanized_cyrillic.txt");

    txt_file.imbue(std::locale ("rus_rus.1251"));

    std::string buf_str;

    while(std::getline (txt_file, buf_str)){
        std::istringstream iss(buf_str);
        std::vector<std::string> letters((std::istream_iterator<std::string>(iss)),
                                         std::istream_iterator<std::string>());

        std::vector<std::u32string > conv_letters;

        for (const auto& x : letters){
               conv_letters.push_back(boost::locale::conv::utf_to_utf < char32_t, char > (convert_locale_to_utf(x)));
        }

        romanized_script.insert(std::pair<std::u32string, std::u32string> (conv_letters[0], conv_letters[2] ));
        romanized_script.insert(std::pair<std::u32string, std::u32string> (conv_letters[1], conv_letters[3] ));

    }

// проверка, что все буквы правильно лежат в мапе
//    for (const auto& x : romanized_script){
//        std::cout << convert_utf_to_locale(boost::locale::conv::utf_to_utf < char, char32_t >(x.first)) << " " <<
//        boost::locale::conv::utf_to_utf < char, char32_t >(x.second) << "\n";
//
//    }
//    std::cout << "\n";


    std::string str;
    std::cin >> str;

    std::string u8str = convert_locale_to_utf(str);
    std::u32string u32str  = boost::locale::conv::utf_to_utf < char32_t, char > (u8str);

    std::u32string result;

    for (auto  s : u32str) {
        result += romanized_script[std::u32string(1, s)];
    }

    std::cout << convert_utf_to_locale(boost::locale::conv::utf_to_utf < char, char32_t > (result));

    return 0;
}
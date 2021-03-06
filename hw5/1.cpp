#include <iostream>
#include <iomanip>
#include <Windows.h>

int main(){

    std::locale locale_1("it_it.utf-8");
    std::locale locale_0("ru_ru.utf-8");

    std::cout << "Converter from RUB to EUR\n";

    long double value;
    std::cin.imbue(locale_0);
    std::cin >> std::get_money(value);

    value /= 88.59;

    SetConsoleOutputCP(CP_UTF8);
    std::cout.imbue(locale_1);
    std::cout  << std::showbase << std::put_money(value, false) << std::endl;

    return 0;
}
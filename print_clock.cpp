#include <chrono>
#include <iomanip>
#include <iostream>

template < typename C >
void print_clock_data()
{
    std::cout << "precision: " << std::setprecision(12) << std::fixed <<
              1.0 * C::period::num / C::period::den << " (seconds)" << std::endl;

    std::cout << "is_steady: " << std::boolalpha << C::is_steady << std::endl;
}

int main(int argc, char ** argv)
{
    std::cout << "system_clock: " << std::endl;
    print_clock_data < std::chrono::system_clock > ();
    std::cout << "high_resolution_clock: " << std::endl;
    print_clock_data < std::chrono::high_resolution_clock > ();
    std::cout << "steady_clock: " << std::endl;
    print_clock_data < std::chrono::steady_clock > ();

    system("pause");

    return EXIT_SUCCESS;
}
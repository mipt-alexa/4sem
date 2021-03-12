#include <filesystem>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;


void view_directory(const std::filesystem::path & path)
{
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
    {
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            if(entry.exists()) {
                auto file_name = entry.path().stem().string();
                auto file_type = entry.path().extension().string();

                if (file_type.empty()) {
                    file_type = "dir";
                }

                auto last_time = entry.last_write_time().time_since_epoch().count();

                last_time = last_time / 10000000;

                std::time_t t = last_time;

                std::cout << std::left << std::setw(20) << file_name <<std::setw(5)<< file_type << " " <<
                std::asctime(std::localtime(&t));
            }
        }
    }
}


int main(){

    std::filesystem::path p = "C:/Users/User/cpp_4sem";

    view_directory(p);

    //RESULT:
    //
    //
//    main                .cpp  Sun Feb  4 17:48:52 2390

    return 0;
}

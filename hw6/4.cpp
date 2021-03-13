#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <filesystem>

#include "json.hpp"

using nlohmann::json;


struct Human {

    std::string name;
    std::string favourite_color;
    unsigned int id;
    float f;

    explicit Human(std::string n = "", std::string fav = "", unsigned int i = 0, float f = 0.0) :
    name(std::move(n)), favourite_color(std::move(fav)), id(i), f(f)
    {}

    friend std::istream &operator>>(std::istream &in, Human &human);
};

std::istream& operator>> (std::istream &in, Human &human){
    in >> human.name >> human.favourite_color >> human.id >> human.f;

    return in;
}



int main(){

    const int n = 3;
    std::vector<Human> humans(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> humans[i];
    }

    auto path = std::filesystem::current_path();

    for (int i = 0; i < n; ++i) {
         std::filesystem::create_directory(path / "../hw6/4_jsons");
    }

    std::vector<json> j(n);
    std::vector< std::fstream > fout(n);

    for (int i = 0; i < n; ++i) {

        j[i]["name"] = humans[i].name;
        j[i]["favourite_color"] = humans[i].favourite_color;
        j[i]["id"] = humans[i].id;
        j[i]["f"] = humans[i].f;

        fout[i].open("../hw6/4_jsons/" + std::to_string(i) + ".txt", std::ios::out);

        fout[i] <<  std::setw(4) << j[i];
     }

    return 0;
}
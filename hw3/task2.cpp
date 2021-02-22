#include <iostream>
#include <set>
#include <random>
#include <fstream>


unsigned long long my_hash(double value){

    unsigned long long h;
    memcpy( &h, &value, sizeof( double ) );
    return h & 0xffffffff;

};


int main(){

    std::ofstream txt_file;
    txt_file.open("../hw3/mydata2.txt");

    std::set<unsigned long long> set;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    std::uniform_real_distribution<> dis_double(DBL_MIN, DBL_MAX);

    int n = 20;
    std::vector<unsigned int> sizes;   //stores numbers of elements
    int n_min = 10000, n_max = 1000000;    // min and max sizes
    int step = (n_max - n_min) / n;
    for (int j = 0; j < n; ++j) {
        sizes.push_back(n_min + j*step);
    }

    for (auto size : sizes) {
        //calculating hashes
        for (int i = 0; i < size; ++i) {
            set.insert(my_hash(dis_double(gen)) % size);
        }

        txt_file << size << " " << size - set.size() << std::endl;

        set.clear();
    }

    // RESULTS
    //
    // Детерминированность и независимость времени вычисления от размера таблицы очевидны...
    //
    // Равномерность проверили с помощью графика числа коллизий от размера таблицы

    return 0;

}
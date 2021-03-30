#include <future>
#include <iostream>

void calculate_block(int a){
    std::cout << a;
}

int main(){

    int block_size = 4;

    std::vector< std::future< void > > futures(4);
    std::atomic< uint64_t > inner = 0;

    for(auto & future : futures){

        future = std::async(calculate_block, block_size);

        future.get();
    }
}

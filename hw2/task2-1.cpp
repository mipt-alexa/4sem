#include <vector>
#include <iostream>

std::vector<int> v;

void my_print(){   // prints the capacity and size of my vector
    std::cout << "capacity: " << v.capacity() << "\n";
    std::cout << "size: " << v.size() << "\n\n";
}

int main(){

    my_print();
    v.resize(15);
    my_print();  // capacity = size = 15

    v.push_back(2);
    my_print(); // new capacity is  22

    std::vector<float> mem_ratio;  // stores ratios of new / old capacity
    float current_cap;

    for (int i = 0; i < 20; ++i) {  // lets increase the size so it becomes bigger than capacity
    current_cap = v.capacity();
    v.resize(v.capacity()+1);
    //my_print();
    mem_ratio.push_back(v.capacity()/current_cap);
    }

    my_print();

    std::cout << "capacity ratio: ";
    for (auto j : mem_ratio){  // capacity ratio is 1.5 (exact expression is new_capacity = floor(1.5 * current_capacity))
        std::cout << j << " ";
    }

    // with too big sizes program fails to run with exit code 1073741855  0x4000001f (visual studio)
    // i couldn't find clear description of this error...

    // or exception std::bad_alloc (mingw)
    // (also mingw compiler uses 2 as capacity ratio)


    // 2 part: using reserve
    std::cout << "\n\n\n";

    v.resize(10);
    v.shrink_to_fit();  // size = 10, capacity = 10
    my_print();

    v.reserve(5);  // if reserved capacity < current, nothing changes, capacity = 10
    my_print();

    v.reserve(100);     // capacity = 100
    my_print();

    v.resize(99);   // size = 99, capacity = 100
    my_print();

    // while size < reserved capacity, capacity doesnt change

    v.resize(101);   // size = 101, capacity = 150
    my_print();

    // if size > reserved capacity, as before capacity ratio is 1.5


    return 0;
}
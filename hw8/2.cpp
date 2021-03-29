#include <random>
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <string>


class Safe_size_t_vec{

public:
    void push_back(std::size_t value){
        std::lock_guard < std::mutex > lock(m_mutex);
        m_vector.push_back(value);
        m_condition_variable.notify_one();
    }

    Safe_size_t_vec() = default;

    std::vector< std::size_t > m_vector;

private:
    std::mutex m_mutex;
    std::condition_variable m_condition_variable;
};


std::string generate_string(const unsigned int str_length){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution< int > dis(0, 3);

    std::vector< char > letters = {'A', 'G', 'T', 'C'};

    std::string str;

    for (int i = 0; i < str_length; ++i) {
        str.push_back(letters[dis(gen)]);
    }

    std::cout << str << "\n";

    return str;
}


void find_all_inclusions(const std::string& str, const std::string& pattern,
                         std::size_t first, std::size_t last, Safe_size_t_vec& positions){

    std::size_t pos = str.find(pattern, first);

    while (pos != std::string::npos && pos < last) {

        positions.push_back(pos);
        pos = str.find(pattern, pos+1);
     }
}



std::vector< std::size_t > parallel_find (std::string data, std::string pattern){

    Safe_size_t_vec pos;

    std::size_t num_threads = std::min(std::thread::hardware_concurrency(),
                                       data.length() / pattern.length());

    std::size_t block_size = data.length() / num_threads;

    std::vector< std::future< void > > futures(num_threads);

    std::vector< std::size_t> start(num_threads), finish(num_threads);

    for (int i = 0; i < num_threads; ++i) {

        start[i] = i*block_size;
        finish[i] = (i + 1)*block_size;
    }

    finish[num_threads - 1] = data.length();

    for (int i = 0; i < num_threads; ++i) {

        futures[i] = std::async(find_all_inclusions, std::ref(data), std::ref(pattern),
                                start[i], finish[i], std::ref(pos));

    }

    for(auto & future : futures){
        future.get();
    }

    return pos.m_vector;

}


int main(){
    
    std::string data = generate_string(100);

    std::string pattern;

    std::getline(std::cin, pattern);

    std::vector< std::size_t > positions = parallel_find(data, pattern);

     for(auto x : positions){
         std::cout << x << "\n";
     }
}

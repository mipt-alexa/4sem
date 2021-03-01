#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <random>


using namespace std;

int main(){

    vector<int> v1(10);

    // 1
    iota(begin(v1), end(v1), 1);

    // 2
     copy(istream_iterator < int > (cin),
            istream_iterator < int > (),
            back_inserter(v1));


    //3
    random_device rd;
    mt19937 g(rd());
    shuffle(begin(v1), end(v1), g);

    // 4
    sort(begin(v1), end(v1));
    auto last = unique(begin(v1), end(v1));
    v1.erase(last, end(v1));

    // 5
    int counter = count_if(begin(v1), end(v1), [](int x) { return ! (x % 2);});
    cout << counter << "\n";

    //6
    auto p = minmax_element(begin(v1), end(v1));
    cout << *(p.first) << "  " << *(p.second) << "\n";

    //7
    int prime_counter = count_if(begin(v1), end(v1), [](int x) {
        if (x <= 1) return false;
        bool is_prime = true;
            for (int i = 2; i*i <= x; ++i) {
                    if (x % i == 0) {
                    is_prime = false;
                    break;
            }
        }
        return is_prime;
    });
    cout << prime_counter << "\n";


    //8
    for_each(begin(v1), end(v1), [](int& x) { x = x * x; });

    //9
    vector<int> v2(v1.size());
    generate(begin(v2), end(v2), g);

    //10
    int sum = accumulate(begin(v2), end(v2), 0);
    cout << sum << "\n";

    //11
    fill_n(begin(v2), 4, 1);

    //12
    vector<int> v3(v1.size());
    transform (v1.begin(), v1.end(), v2.begin(), v3.begin(), minus<>());

    //13
    for_each(begin(v3), end(v3), [](int& x) {if(x < 0) x = 0;});

    //14
    last = remove(begin(v3), end(v3), 0);
    v3.erase(last, end(v3));

    //15
    reverse(begin(v3), end(v3));

    //16
    nth_element(begin(v3), prev(end(v3), 3), end(v3));

    //17
    sort(begin(v1), end(v1));
    sort(begin(v2), end(v2));

    //18
    vector<int> v4;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v4));

    //19
    auto er = equal_range(begin(v4), end(v4), 1);
    cout << *er.first << " " << *er.second;

    //20
    cout << "\n";
    copy(v1.begin(), v1.end(),ostream_iterator < int > (cout, " "));
    cout << "\n";
    copy(v2.cbegin(), v2.cend(),ostream_iterator < int > (cout, " "));
    cout << "\n";
    copy(v3.cbegin(), v3.cend(),ostream_iterator < int > (cout, " "));
    cout << "\n";
    copy(v4.cbegin(), v4.cend(),ostream_iterator < int > (cout, " "));
    cout << "\n";



    //21

    v4.resize(100);
    generate(begin(v4), end(v4), g);
    v3.clear();
    copy (begin(v4), end(v4), back_inserter(v3));

    counter = 0;
    sort(begin(v4), end(v4), [&counter](int x, int y) {counter++; return x < y;});
    cout << "counts in sort: " << counter << "\n";

    counter = 0;
    nth_element(begin(v3), prev(end(v3), v3.size()/2), end(v3),
                [&counter](int x, int y) {counter++; return x < y;});
    cout << "counts in nth_element: " << counter << "\n";

    return 0;
}
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

int main(){

   /* default_random_engine dre(chrono::system_clock::now().time_since_epoch().count());

    mt19937_64 mt;

    uniform_int_distribution <> uid(0,100);
    uniform_real_distribution <> urd(0.0, 100);

    cout << uid(mt) << endl;

    auto l = [](int x) {return x+1;};
    function< int(int)> l2 = [](int x) {return x+1;};

    cout << l(42) << "\n";

    vector<int> a = {2, 3, 2, 5};

    auto counter = 0U;

    sort(begin(a), end(a),
         [&counter](auto a, const auto & b) {counter++; return a < b;});


    cout << typeid(l).name() << "\n";

    cout << counter << "\n";
    */

    vector<int> v0 = {0, 5, 4, 4};
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    /*

    for_each(begin(v0), end(v0), [](auto x) {cout << x << "\n";});
    cout << count_if(begin(v0), end(v0), [](auto x) {return x % 2;}) << "\n";

    auto result = minmax_element(begin(v0), end(v0));
    cout << *result.second << "\n";

    auto r = find_if(begin(v0), end(v0), [](auto x) {return x==3;});

    if (r != end(v0)){
        cout << *r;
    }

    for_each(begin(v0), end(v0), [](auto & x){cout << x;});

    copy(begin(v0), end(v0), ostream_iterator<int>(cout, "\n"));

    transform(begin(v0), end(v0), back_inserter(v1), [](auto x) {return x*x;});

    transform(begin(v0), end(v0), begin(v0), begin(v0), [](auto x) {return x*x;});

    */

    iota(begin(v0), end(v0),  [])( ) {});

    __LINE__;

    return 0;
}

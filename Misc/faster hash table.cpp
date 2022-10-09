// Usage
// To use this data structure:

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> table;


// Defeating Anti-Hash tests
// One weakness of hash tables is that mean people can find hash collisions offline and blow up the complexity of your hashmap. In my opinion, the easiest way of solving this is below. There's no need to define your own custom hash function.

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<key, int, chash> table;
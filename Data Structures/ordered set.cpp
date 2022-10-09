#include <bits/extc++.h>
using namespace __gnu_pbds;

template<class key, class cmp = less<key>>
using ordered_set = tree<key, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// order_of_key(X)  : Returns number of items strictly smaller than X 
// find_by_order(k) : Returns itr of k-th element in a set (counting from zero)
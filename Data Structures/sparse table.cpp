// const ll Mx = 600100;

// ll LG[Mx];

// void pre_log()
// {
//   LG[1] = 0;
//   for(ll i = 2; i < Mx; i++)
//    LG[i] = LG[i >> 1] + 1;
// }

// usage -- idempotent function
// auto fun = [&](ll x, ll y) { return min(x, y); }; 
// SparseTable<ll, decltype(fun)> st(arr, fun);
template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable 
{
  ll N;
  vector<vector<T>> mat;
  F func;
  
  SparseTable() {}
  // usage -- for vector of spt's
  // vector < SparseTable<ll> > v1(m);
  // v1[i] = SparseTable<ll>(arr2d[i], fun);

  SparseTable(const vector<T>& a, const F& f) : func(f) // O(NLogN)
  {
    N = sz(a);
    ll max_log = 64 - __builtin_clzll(N); // LG[N] + 1;
    mat.resize(max_log);
    mat[0] = a;
    for(ll j = 1; j < max_log; j++) 
    {
      mat[j].resize(N - (1 << j) + 1);
      for(ll i = 0; i <= N - (1 << j); i++) 
      {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(ll from, ll to) const // O(1)
  {
    assert(0 <= from && from <= to && to <= N - 1);
    ll lg = 64 - __builtin_clzll(to - from + 1) - 1; // LG[to - from + 1];
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};
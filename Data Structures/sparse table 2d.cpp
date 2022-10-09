const ll Mx = 1010;
const ll LGMx = 64 - __builtin_clzll(Mx);
int table[LGMx][LGMx][Mx][Mx];

// usage -- idempotent function
// auto fun = [&](int x, int y) { return min(x, y); }; 
// SparseTable2D<int, decltype(fun)> st(arr2D, fun);

template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable2D
{
  ll N, M;
  F func;

  SparseTable2D(const vector<vector<T>>& a, const F& f) : func(f) // O(NMLogNlogM)
  {
    N = sz(a), M = sz(a[0]);
    ll lgN = 64 - __builtin_clzll(N);
    ll lgM = 64 - __builtin_clzll(M);

    // building sparse table for each row
    for(ll ir = 0; ir < N; ir++)
    {
      for(ll ic = 0; ic < M; ic++)
        table[0][0][ir][ic] = a[ir][ic];

      for(ll jc = 1; jc < lgM; jc++)
      {
        for(ll ic = 0; ic <= M - (1 << jc); ic++)
          table[0][jc][ir][ic] = func(table[0][jc - 1][ir][ic], table[0][jc - 1][ir][ic + (1 << (jc - 1))]);
      }
    }

    // building the entire table
    for(ll jr = 1; jr < lgN; jr++)
      for(ll ir = 0; ir < N; ir++)
        for(ll jc = 0; jc < lgM; jc++)
          for(ll ic = 0; ic < M; ic++)
             table[jr][jc][ir][ic] = func(table[jr-1][jc][ir][ic], table[jr-1][jc][ir + (1 << (jr - 1))][ic]);
  }

  T get(ll x1, ll y1, ll x2, ll y2) const // O(1)
  {
    assert(0 <= x1 && 0 <= y1 && x1 <= x2 && y1 <= y2 && x2 <= N - 1 && y2 <= M - 1);
    ll lgx = 64 - __builtin_clzll(x2 - x1 + 1) - 1;
    ll lgy = 64 - __builtin_clzll(y2 - y1 + 1) - 1;
    T R1 = func(table[lgx][lgy][x1][y1], table[lgx][lgy][x1][y2 - (1 << lgy) + 1]); 
    T R2 = func(table[lgx][lgy][x2 - (1 << lgx) + 1][y1], table[lgx][lgy][x2 - (1 << lgx) + 1][y2 - (1 << lgy) + 1]);
    return func(R1, R2);
  }
};
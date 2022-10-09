struct BIT
{
  ll N;
  vector<ll> T;
 
  BIT(ll n)
  {
    N = n;
    T.assign(N + 1, 0);
  }
 
  ll pref(ll x)
  {
    ll res = 0;
    while (x > 0)
    {
      res += T[x];
      x -= (x & (-x));
    }
    return res;
  }
 
  void add(ll x, ll val)
  {
    while (x <= N)
    {
      T[x] += val;
      x += (x & (-x));
    }
  }
 
  ll rsum(ll a, ll b)
  {
    return pref(b) - pref(a - 1);
  }
};
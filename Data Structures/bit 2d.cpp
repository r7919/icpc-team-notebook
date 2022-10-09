struct BIT
{
  ll N;
  vector<ll> T;

  BIT(ll n)
  {
    N = n;
    T.assign(N + 1, 0);
  }

  void add(ll x, ll val)
  {
    while (x <= N)
    {
      T[x] += val;
      x += (x & -x);
    }
  }

  ll psum(ll x)
  {
    ll res = 0;
    while (x > 0)
    {
      res += T[x];
      x -= (x & -x);
    }
    return res;
  }

  ll rsum(ll a, ll b)
  {
    return psum(b) - psum(a - 1);
  }
};

struct BIT2D
{ 
  ll N, M;
  vector<BIT> T;

  BIT2D(ll n, ll m)
  {
    N = n;
    M = m;
    T.assign(N + 1, BIT(M));
  } 

  void add(ll x, ll y, ll val)
  {
    while (x <= N)
    {
      T[x].add(y, val);
      x += (x & -x);
    } 
  }

  ll psum(ll x, ll y)
  {
    ll res = 0;
    while (x > 0)
    {
      res += T[x].psum(y);
      x -= (x & -x);
    }
    return res;
  }

  ll rsum(ll x1, ll y1, ll x2, ll y2)
  {
    return psum(x2, y2) - psum(x1 - 1, y2) - psum(x2, y1 - 1) + psum(x1 - 1, y1 - 1);
  }
};
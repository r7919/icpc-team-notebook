const ll MOD = 1e9+7; 

namespace mod_op
{
  ll madd(ll a, ll b) 
  {
    return (a + b) % MOD;
  }

  ll mmul(ll a, ll b) 
  {
    return ((a % MOD) * (b % MOD)) % MOD;
  }

  ll msub(ll a, ll b) 
  {
    return (((a - b) % MOD) + MOD) % MOD;
  }

  ll mpow(ll a, ll b) 
  {
    a %= MOD;
    ll res = 1;
    while (b > 0) 
    {
      if (b & 1) 
        res = mmul(res, a);
      a = mmul(a, a);
      b >>= 1;
    }
    return res;
  }

  ll minv(ll a) 
  {
    return mpow(a, MOD - 2);
  }

  ll mdiv(ll a, ll b) 
  {
    return mmul(a, minv(b));
  }
}

using namespace mod_op;


const ll MXN = 1e6;

ll factorial[MXN + 1];
ll inv_factorial[MXN + 1];

void prepare_factorials()
{
  factorial[0] = 1;
  for (ll i = 1; i <= MXN; i++)
    factorial[i] = mmul(factorial[i - 1], i);

  inv_factorial[MXN] = minv(factorial[MXN]);

  for (ll i = MXN - 1; i >= 0; i--)
    inv_factorial[i] = mmul(inv_factorial[i + 1], i + 1);
}
 
ll ncr(ll n, ll r)
{
  if (n < 0 || r < 0 || r > n)
    return 0ll;
  else
    return mmul(factorial[n], mmul(inv_factorial[n - r], inv_factorial[r]));
}
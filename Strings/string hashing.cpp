// https://codeforces.com/blog/entry/60445
// https://cp-algorithms.com/string/string-hashing.html
// https://cp-algorithms.com/string/rabin-karp.html

// version: int (faster)

// Usage for MultiHash: (pick random p if needed to avoid hacks)
// StringHash sh1(n, s);
// StringHash sh2(n, s, 97, 1e9+9);

struct StringHash
{
  int N, P, M, iP;
  vector<int> pow, inv, prefix;
 
  StringHash() {}
 
  StringHash(int n, string s, int p = 89, int m = 1e9+7)
  {
    N = n, P = p, M = m;
    iP = minv(P);
    pow.resize(N);
    inv.resize(N);
    prefix.resize(N);
 
    inv[0] = pow[0] = 1;
 
    for (int i = 1; i < N; i++)
    {
      pow[i] = mmul(pow[i - 1], P);
      inv[i] = mmul(inv[i - 1], iP);
    }
 
    prefix[0] = (s[0] - '0' + 1);
 
    for (int i = 1; i < N; i++)
      prefix[i] = madd(prefix[i - 1], mmul(s[i] - '0' + 1, pow[i]));
  }
 
  int get(int l, int r)
  {
    if (l == 0)
      return prefix[r];
    else
      return mmul(msub(prefix[r], prefix[l - 1]), inv[l]);
  }
  // mint with M
};

// version: ll (generic)

vector<ll> bases = 
{
  random(89, 1000),
  random(89, 1000),
  ...
}; 

vector<ll> primes = 
{
  1000000007,1000000009,1000000021,
  1000000033,1000000087,1000000093,
  1000000097,1000000103,1000000123,1000000181
};

template<ll K>
struct MultiHash
{
  StringHash sh[K];

  MultiHash(ll n, string s)
  {
    for (ll i = 0; i < K; i++)
      sh[i] = StringHash(n, s, bases[i], primes[i]);
  } 

  vector<ll> get(ll l, ll r)
  {
    vector<ll> res(K);
    for (ll i = 0; i < K; i++)
      res[i] = sh[i].get(l, r);
    return res;
  }
};
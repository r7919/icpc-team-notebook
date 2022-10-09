namespace factorizer
{
  const ll N = 200200;
  ll lp[N + 1];
  vector<ll> pr;

  void sieve()
  {
    for (ll i = 2; i <= N; ++i)
    {
      if (lp[i] == 0)
      {
        lp[i] = i;
        pr.push_back(i);
      }

      for (ll j = 0; j < ll(pr.size()) && pr[j] <= lp[i] && 1LL * i * pr[j] <= N; j++)
        lp[i * pr[j]] = pr[j];
    }
  }

  vector<array<ll, 2>> pfact(ll x)
  {
    vector<array<ll, 2>> factors;
    while (x > 1)
    {
      ll cnt = 0;
      ll p = lp[x];
      while (x % p == 0)
      {
        x /= p;
        cnt++;
      }
      factors.push_back({p, cnt});
    }
    return factors;
  }

  vector<ll> build_divisors(vector<array<ll, 2>> &factors)
  {
    vector<ll> divisors = {1};
    for (auto &p : factors)
    {
      ll size = ll(divisors.size());
      for (ll i = 0; i < size; i++)
      {
        ll cur = divisors[i];
        for (ll j = 0; j < p[1]; j++)
        {
          cur *= p[0];
          divisors.push_back(cur);
        }
      }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
  }

  vector<ll> divisors(ll x)
  {
    vector<array<ll, 2>> factors = pfact(x);
    return build_divisors(factors);
  }
}

using namespace factorizer;
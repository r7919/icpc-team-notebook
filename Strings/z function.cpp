// https://cp-algorithms.com/string/z-function.html

// Note:
// z[i] is the length of the longest common prefix between s and the suffix of s starting at i
// z[0] = 0 (not well defined)
// [l, r] is the known right most range that has matched with prefix of s
// Each iteration of the while loop will increase the right border r of the match segment.
// Since r can't be more than n - 1, this means that the inner while loop won't make more than n - 1 iterations

vector<ll> z_function(string s)
{
  ll n = s.size();
  vector<ll> z(n);
  z[0] = 0;

  for (ll i = 1, l = 0, r = 0; i < n; i++)
  {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      z[i]++;
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }

  return z;
}
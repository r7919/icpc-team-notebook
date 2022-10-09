// https://cp-algorithms.com/string/prefix-function.html

// Note:
// pi[i] is length of the longest proper prefix which is also a suffix of the substring s[0...i] 
// pi[0] = 0
// The values of the prefix function can only increase by at most one
// Time complexity is O(n) because: pi[i] <= pi[i - 1] + 1
// - Each character can add most one to pi. and each, time we go back, the matching decreases by at least 1. 
// - So we can deduce that the number of times the inner while loop runs cannot be more than O(n).

vector<ll> prefix_function(string s)
{
  ll n = s.size();
  vector<ll> pi(n);
  pi[0] = 0;

  for (ll i = 1; i < n; i++)
  {
    ll j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }

  return pi;
}
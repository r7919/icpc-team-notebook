// https://cp-algorithms.com/string/manacher.html

// Note:
// d1[i] -> stores number of odd palindromes centered at i
// d2[i] -> stores number of even palindromes centered at (i - 1, 'i')
// (l, r) maintains borders of the rightmost found sub-palindrome (i. e. the palindrome with maximal r).
// Each iteration of the while loop will increase the right border r of the match segment.
// Since r can't be more than n - 1, this means that the inner while loop won't make more than n - 1 iterations

vector<ll> manachers_odd(string s)
{
  ll n = s.size();
  vector<ll> d1(n);
 
  for (ll i = 0, l = 0, r = -1; i < n; i++)
  {
    if (i <= r)
      d1[i] = min(r - i + 1, d1[l + r - i]);
    else
      d1[i] = 1;
    while (0 <= i - d1[i] && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]])
      d1[i]++;
    if (i + d1[i] - 1 > r)
    {
      l = i - d1[i] + 1;
      r = i + d1[i] - 1;
    }
  }
 
  return d1;
}
 
vector<ll> manachers_even(string s)
{
  ll n = s.size();
  vector<ll> d2(n);
 
  for (ll i = 0, l = 0, r = -1; i < n; i++)
  {
    if (i <= r)
      d2[i] = min(r - i + 1, d2[l + r - i + 1]);
    else
      d2[i] = 0;
    while (0 <= i - d2[i] - 1 && i + d2[i] < n && s[i - d2[i] - 1] == s[i + d2[i]])
      d2[i]++;
    if (i + d2[i] - 1 > r)
    {
      l = i - d2[i];
      r = i + d2[i] - 1;
    }
  }
 
  return d2;
}
// version 1.0 - number of numbers with some property in [L, R]

ll dp[10010][2][2][110];

void solve()
{
  string L = "1";
  string R;
  ll d; cin >> R >> d; 

  // make both L, R of same length by appending 0's to L if needed
  L = string((ll) R.size() - (ll) L .size(),'0') + L;
  ll N = (ll) L.size();

  memset(dp, -1, sizeof(dp));

  /*
    level -> level in trie (msb -> lsb)
    bl    -> is 1 if the state is bounded by l 
    br    -> is 1 if the state is bounded by r 
    smd   -> sum of digits so far mod d 

    - initially we are at root (level = 0), where both l, r are bounded(/   \)
    - each leaf node of trie represents a number 

    dp(level, bl, br, smd) is the number of numbers with sum of digits % d = 0 
    where we have sum smd already, with given bounds

    The overlapping sub-problems can be observed after looking at trie (msb -> lsb)
  */

  function<ll(ll, ll, ll, ll)> rec = [&](ll level, ll bl, ll br, ll smd)
  {
    if (level == N)
    {
      if (smd == 0)
        return 1ll;
      else
        return 0ll;
    }

    if (dp[level][bl][br][smd] != -1)
      return dp[level][bl][br][smd];

    ll ans = 0;

    ll l = 0, r = 9;
    if (bl)
      l = L[level] - '0';
    if (br)
      r = R[level] - '0';

    for (ll i = l; i <= r; i++)
    {
      ll bl_i = bl, br_i = br;

      if (i != L[level] - '0')
        bl_i = 0;
      if (i != R[level] - '0')
        br_i = 0;

      ans = madd(ans, rec(level + 1, bl_i, br_i, (smd + i) % d));
    }

    return dp[level][bl][br][smd] = ans;
  };

  cout << rec(0, 1, 1, 0) << "\n";
}

// version 2.0 - number of pairs with some property in [L, R]

// Problem:
// F(x) = sum of digits of number x.

// Given a number N, find the number of pairs (x,y) such that -
// 0 ≤ x < y ≤ N
// F(x) < F(y)
// F(x) + F(y) is prime.

int dp[51][2][2][2][2][460][460][2];

void solve()
{
  vector<int> pcache(1010, -1);

  auto is_prime = [&](int n)
  {
    if (n <= 1)
      return 0;

    if (pcache[n] != -1)
      return pcache[n];

    int ans = 1;

    for (int i = 2; i * i <= n; i++)
    {
      if (n % i == 0)
      {
        ans = 0;
        break;
      }
    }

    return pcache[n] = ans;
  };

  memset(dp, -1, sizeof(dp));

  string L = "0";
  string R; cin >> R;
  L = string(int(R.size()) - int(L.size()), '0') + L; 
  int N = L.size();

  // g -> 1 if x < y, 0 if x == y so far

  function<int(int, int, int, int, int, int, int, int)> rec = [&](int level, int blx, int brx, int bly, int bry, int sx, int sy, int g)
  {
    if (level == N)
    {
      if (is_prime(sx + sy) && (sx < sy) && (g == 1))
        return 1;
      else
        return 0;
    }

    if (dp[level][blx][brx][bly][bry][sx][sy][g] != -1)
      return dp[level][blx][brx][bly][bry][sx][sy][g];

    int lx = 0, rx = 9, ly = 0, ry = 9;
    if (blx)
      lx = L[level] - '0';
    if (brx)
      rx = R[level] - '0';
    if (bly)
      ly = L[level] - '0';
    if (bry)
      ry = R[level] - '0';

    int ans = 0;

    for (int i = lx; i <= rx; i++)
    {
      int blx_i = blx, brx_i = brx;

      if (i != L[level] - '0')
        blx_i = 0;
      if (i != R[level] - '0')
        brx_i = 0;

      for (int j = ly; j <= ry; j++)
      {
        int bly_j = bly, bry_j = bry;

        if (j != L[level] - '0')
          bly_j = 0;
        if (j != R[level] - '0')
          bry_j = 0;

        int g_ij = g;

        if (g == 0)
        {
          if (level == N - 1)
          {
            if (i >= j)
              continue;
            else
              g_ij = 1;
          }
          else
          {
            if (i > j)
              continue;
            else if (i < j)
              g_ij = 1;
          }
        }

        ans = madd(ans, rec(level + 1, blx_i, brx_i, bly_j, bry_j, sx + i, sy + j, g_ij));
      }
    }

    return dp[level][blx][brx][bly][bry][sx][sy][g] = ans;
  };

  cout << rec(0, 1, 1, 1, 1, 0, 0, 0) << "\n";
}
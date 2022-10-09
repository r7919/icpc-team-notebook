// https://cses.fi/problemset/task/1672/
// https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html

void solve()
{
  ll n, m, q; 
  cin >> n >> m >> q;

  vector<vector<ll>> d(n, vector<ll>(n, INF));

  for (ll i = 0; i < m; i++)
  {
    ll x, y, w;
    cin >> x >> y >> w;
    x--; y--;
    d[x][y] = min(d[x][y], w);
    d[y][x] = min(d[y][x], w);
  }  

  for (ll i = 0; i < n; i++)
    d[i][i] = 0;

  for (ll k = 0; k < n; k++)
    for (ll i = 0; i < n; i++)
      for (ll j = 0; j < n; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

  for (ll i = 0; i < q; i++)
  {
    ll x, y; cin >> x >> y;
    x--; y--;
    cout << ((d[x][y] == INF) ? -1 : d[x][y]) << "\n"; 
  }
}
// https://cp-algorithms.com/graph/dijkstra.html
// https://cses.fi/problemset/task/1671/

void solve()
{
  ll n, m; cin >> n >> m;
  vector<vector<array<ll, 2>>> adj(n);

  for (ll i = 0; i < m; i++)
  {
    ll x, y, w;
    cin >> x >> y >> w;
    x--; y--;
    adj[x].push_back({y, w});  
  }   

  vector<ll> d(n, INF);
  set<array<ll, 2>> q;
  q.insert({0, 0}); 
  d[0] = 0;

  while (!q.empty())
  {
    ll v = (*q.begin())[1];
    q.erase(q.begin());

    for (auto edge: adj[v])
    {
      ll u = edge[0];
      ll w = edge[1];
      if (d[u] > d[v] + w)
      {
        q.erase({d[u], u});
        d[u] = d[v] + w;
        q.insert({d[u], u});
      }
    }
  }

  for (auto x: d)
    cout << x << " ";
  cout << "\n";
}
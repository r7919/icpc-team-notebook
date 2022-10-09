// https://www.codechef.com/problems/REVERSE
// https://www.codechef.com/viewsolution/48525003
// https://cp-algorithms.com/graph/01_bfs.html

void solve()
{
  ll n, m; cin >> n >> m;
  vector<vector<array<ll, 2>>> adj(n);

  for (ll i = 0; i < m; i++)
  {
    ll x, y; cin >> x >> y;
    x--; y--;
    adj[x].push_back({y, 0});
    adj[y].push_back({x, 1}); 
  }  

  deque<ll> q;
  vector<ll> d(n, INF);
  q.push_back(0);
  d[0] = 0;

  while (!q.empty())
  {
    ll v = q.front();
    q.pop_front();

    for (auto edge: adj[v])
    {
      ll u = edge[0];
      ll w = edge[1];
      if (d[u] > d[v] + w)
      {
        d[u] = d[v] + w;
        if (w == 1)
          q.push_back(u);
        else
          q.push_front(u);
      }
    }
  }

  if (d[n - 1] == INF)
    cout << "-1" << "\n";
  else
    cout << d[n - 1] << "\n";
}
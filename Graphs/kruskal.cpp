// https://cp-algorithms.com/graph/mst_kruskal.html
// https://cses.fi/problemset/task/1675/

void solve()
{
  ll n, m; cin >> n >>m;
  vector<array<ll, 3>> edges;

  for (ll i = 0; i < m; i++)
  {
    ll x, y, w; 
    cin >> x >> y >> w;
    x--; y--;
    edges.push_back({w, x, y});  
  }   

  sort(edges.begin(), edges.end());

  UnionFind uf(n);

  ll cost = 0, ecnt = 0;

  for (auto edge: edges)
  {
    if (uf.find(edge[1]) != uf.find(edge[2]))
    {
      cost += edge[0];
      ecnt++;
      uf.merge(edge[1], edge[2]);
    }
  }

  if (ecnt != n - 1)
    cout << "IMPOSSIBLE" << "\n";
  else
    cout << cost << "\n";
}
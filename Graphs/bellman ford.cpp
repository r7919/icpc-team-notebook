// https://cses.fi/problemset/task/1197/
// https://cp-algorithms.com/graph/bellman_ford.html
// https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html

void solve()
{
  ll n, m; cin >> n >> m;
  vector<array<ll, 3>> edges;

  for (ll i = 0; i < m; i++)
  {
    ll x, y, w;
    cin >> x >> y >> w;
    x--; y--;
    edges.push_back({x, y, w}); 
  }  

  vector<ll> d(n, 0), p(n, -1);

  // Note: if we start bellman ford only form 0 we can only find if any negitive cycle reachable from 0
  // so here d[v] is the minimum distance from any vertex to v and it will converge in n - 1 iterations 
  // if it doesn't have a negative cycle.

  ll X = -1; // last changed vetex

  for (ll i = 0; i < n; i++)
  {
    X = -1; // initialized after every iteration

    for (auto e: edges)
    {
      if (d[e[0]] + e[2] < d[e[1]])
      {
        d[e[1]] = max(-INF, d[e[0]] + e[2]);
        p[e[1]] = e[0];
        X = p[e[1]];
      }
    }
  }

  if (X == -1) // no change in the nth iteration
    cout << "NO" << "\n";
  else
  {
    cout << "YES" << "\n";

    // vertex X will either lie in a negative weight cycle, or is reachable from it
    for (ll i = 0; i < n; i++)
      X = p[X];

    // now X will be in the cycle 

    vector<ll> path;

    for (ll i = X; ; i = p[i])
    {
      path.push_back(i);
      if (i == X && path.size() > 1) // completed rotation
        break;
    }

    reverse(path.begin(), path.end());

    for (auto x: path)
      cout << x + 1 << " ";
     cout << "\n";
  }
}
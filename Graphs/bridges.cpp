// https://www.spoj.com/problems/EC_P/
// https://cp-algorithms.com/graph/bridge-searching.html
// https://codeforces.com/blog/entry/68138

// Note: 
// A tree-edge uv is a bridge if and only if there is no back-edge that "passes over" uv.
// A back-edge is never a bridge.

void solve()
{
  ll n, m; cin >> n >> m;
  vector<vector<ll>> adj(n);

  for (ll i = 0; i < m; i++)
  {
    ll x, y; cin >> x >> y;
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x); 
  } 

  ll timer = 1;
  vector<ll> tin(n), low(n), vis(n, 0);
  vector<array<ll, 2>> bridges;

  function<void(ll, ll)> dfs = [&](ll v, ll p)
  {
    vis[v] = 1;
    tin[v] = low[v] = timer++;

    for (auto x: adj[v])
    {
      if (x != p)
      {
        if (!vis[x])
        {
          dfs(x, v);
          low[v] = min(low[v], low[x]);
          if (low[x] > tin[v])
            bridges.push_back({min(x, v) + 1, max(x, v) + 1});
        }
        else
          low[v] = min(low[v], tin[x]);
      }
    }
  };

  for (ll i = 0; i < n; i++)
  {
    if (!vis[i])
      dfs(i, -1);
  } 

  sort(bridges.begin(), bridges.end());

  if (bridges.empty())
    cout << "Sin bloqueos" << "\n";
  else
  {
    cout << bridges.size() << "\n";
    for (auto p: bridges)
      cout << p[0] << " " << p[1] << "\n";
  }
}
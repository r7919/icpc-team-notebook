// https://www.spoj.com/problems/SUBMERGE/
// https://cp-algorithms.com/graph/cutpoints.html

// Note: 
// A vertex can be an articulation point even if there exists a back-edge going over it 
// i.e if it has multiple children and only some children's subtrees have back-edges that go over it while others don't
// => A vertex is not an articulation point if and only if an edge passes over it from "each of its subtrees".

// The root of the dfs tree is a special case: it is an articulation point if and only if it has more than one child in the dfs tree.

void solve()
{
  ll n, m; cin >> n >> m;

  if (n == 0 && m == 0)
    exit(0);

  vector<vector<ll>> adj(n);

  for (ll i = 0; i < m; i++)
  {
    ll x, y; cin >> x >> y;
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  } 

  ll timer = 1;
  vector<ll> vis(n, 0), tin(n), isAp(n, 0), low(n);

  function<void(ll, ll)> dfs = [&](ll v, ll p)
  {
    vis[v] = 1;
    low[v] = tin[v] = timer++;
    ll children = 0;

    for (auto x: adj[v])
    {
      if (x != p)
      {
        if (!vis[x])
        {
          dfs(x, v);
          low[v] = min(low[v], low[x]);
          if (low[x] >= tin[v] && p != -1)
            isAp[v] = 1;
          children++;
        }
        else
          low[v] = min(low[v], tin[x]);
      }
    }

    if (p == -1 && children > 1)
      isAp[v] = 1; 
  }; 

  for (ll i = 0; i < n; i++)
  {
    if (!vis[i])
      dfs(i, -1);
  }

  cout << accumulate(isAp.begin(), isAp.end(), 0ll) << "\n";
}
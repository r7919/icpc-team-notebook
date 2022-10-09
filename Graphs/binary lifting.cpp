// version: kth ancestor
// Problem: https://cses.fi/problemset/task/1687/

using ll = long long;
const ll MX = 20;

void solve()
{
  ll n, q; cin >> n >> q;
  vector<vector<ll>> adj(n); 

  for (ll i = 1; i < n; i++)
  {
    ll p; cin >> p; p--; 
    adj[i].push_back(p);
    adj[p].push_back(i);
  }

  vector<vector<ll>> up(n, vector<ll>(MX + 1)); 
  vector<ll> depth(n, 0);

  function<void(ll, ll)> dfs = [&](ll node, ll parent)
  {
    up[node][0] = parent;
    for (ll i = 1; i <= MX; i++)
      up[node][i] = up[up[node][i - 1]][i - 1];

    for (auto x: adj[node])
    {
      if (x != parent)
      {
        depth[x] = depth[node] + 1;
        dfs(x, node);
      }
    }
  }; 

  ll root = 0;
  dfs(root, root);

  auto ancestor = [&](ll x, ll d)
  {
    for (ll i = 0; i <= MX; i++)
    {
      if (d & (1ll << i))
        x = up[x][i];
    }
    return x;
  };

  for (ll i = 0; i < q; i++)
  {
    ll v, k; cin >> v >> k;
    v--;
    if (k > depth[v])
      cout << -1 << "\n";
    else
      cout << ancestor(v, k) + 1 << "\n"; 
  } 
}




// version: LCA
// https://cses.fi/problemset/task/1688/

using ll = long long;
const ll MX = 20;

void solve()
{
  ll n, q; cin >> n >> q;
  vector<vector<ll>> adj(n); 

  for (ll i = 1; i < n; i++)
  {
    ll p; cin >> p; p--; 
    adj[i].push_back(p);
    adj[p].push_back(i);
  }

  vector<vector<ll>> up(n, vector<ll>(MX + 1)); 
  vector<ll> depth(n, 0);

  function<void(ll, ll)> dfs = [&](ll node, ll parent)
  {
    up[node][0] = parent;
    for (ll i = 1; i <= MX; i++)
      up[node][i] = up[up[node][i - 1]][i - 1];

    for (auto x: adj[node])
    {
      if (x != parent)
      {
        depth[x] = depth[node] + 1;
        dfs(x, node);
      }
    }
  }; 

  ll root = 0;
  dfs(root, root);

  auto ancestor = [&](ll x, ll d)
  {
    for (ll i = 0; i <= MX; i++)
    {
      if (d & (1ll << i))
        x = up[x][i];
    }
    return x;
  };

  auto lca = [&](ll u, ll v)
  {
    if (depth[u] < depth[v])
      swap(u, v);

    u = ancestor(u, depth[u] - depth[v]);

    if (u == v)
      return u;

    for (ll i = MX; i >= 0; i--)
    {
      if (up[u][i] != up[v][i])
      {
        u = up[u][i];
        v = up[v][i];
      }
    }

    return up[u][0];
  };

  for (ll i = 0; i < q; i++)
  {
    ll a, b; cin >> a >> b;
    a--; b--;
    cout << lca(a, b) + 1 << "\n"; 
  } 
}




// version: Path Min (path aggregates)
// https://codeforces.com/gym/102694/problem/D

using ll = long long;

const ll INF = 1e18;
const ll MX = 20;

void solve()
{
  ll n, edges; cin >> n >> edges;
  vector<vector<array<ll, 2>>> adj(n); 

  for (ll i = 0; i < edges; i++)
  {
    ll x, y; cin >> x >> y;
    ll val; cin >> val;
    x--; y--; 
    adj[x].push_back({y, val});
    adj[y].push_back({x, val});
  }

  vector<vector<ll>> up(n, vector<ll>(MX + 1)); 
  vector<vector<ll>> upMin(n, vector<ll>(MX + 1)); 
  vector<ll> depth(n, 0);

  function<void(ll, ll, ll)> dfs = [&](ll node, ll parent, ll val)
  {
    up[node][0] = parent;
    upMin[node][0] = val;
    for (ll i = 1; i <= MX; i++)
    {
      up[node][i] = up[up[node][i - 1]][i - 1];
      upMin[node][i] = min(upMin[node][i - 1], upMin[up[node][i - 1]][i - 1]);
    }

    for (auto x: adj[node])
    {
      if (x[0] != parent)
      {
        depth[x[0]] = depth[node] + 1;
        dfs(x[0], node, x[1]);
      }
    }
  }; 

  ll root = 0;
  dfs(root, root, INF);

  auto ancestor = [&](ll x, ll d)
  {
    for (ll i = 0; i <= MX; i++)
    {
      if (d & (1ll << i))
        x = up[x][i];
    }
    return x;
  };

  auto lca = [&](ll u, ll v)
  {
    if (depth[u] < depth[v])
      swap(u, v);

    u = ancestor(u, depth[u] - depth[v]);

    if (u == v)
      return u;

    for (ll i = MX; i >= 0; i--)
    {
      if (up[u][i] != up[v][i])
      {
        u = up[u][i];
        v = up[v][i];
      }
    }
    
    return up[u][0];
  };

  auto pathMin = [&](ll u, ll v)
  {
    ll m = lca(u, v), res = INF;
    ll um = depth[u] - depth[m];
    ll vm = depth[v] - depth[m];

    for (ll i = 0; i <= MX; i++)
    {
      if (um & (1ll << i))
      {
        res = min(res, upMin[u][i]);
        u = up[u][i];
      }
    }

    for (ll i = 0; i <= MX; i++)
    {
      if (vm & (1ll << i))
      {
        res = min(res, upMin[v][i]);
        v = up[v][i];
      }
    }

    return res;
  };

  ll q; cin >> q; 
  for (ll i = 0; i < q; i++)
  {
    ll a, b; cin >> a >> b;
    a--; b--;
    ll ans = pathMin(a, b);
    if (ans == INF)
      cout << 0 << "\n";
    else
      cout << ans << "\n";
  } 
}
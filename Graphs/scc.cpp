// https://cp-algorithms.com/graph/strongly-connected-components.html
// https://www.cs.dartmouth.edu/~deepc/Courses/S20/lecs/lec11.pdf

// Kosaraju's two-pass algorithm

// Note:
// DFS guarantees that the vertex(scc) with the biggest finishing time will be in the SOURCE of condensation graph, 
// but the vertex(scc) with the smallest finishing time may not be in SINK of condensation graph.

// Example:
// V = {a, b, c, d}
// E = {ab, ba, ac, cd, dc}
// dfs: a-b-a-c-d-c-a
// when we start dfs at 'a', 'b' has smallest finishing time but it is not in the SINK
// 'a' has the largest finishing time it is in the SOURCE of G_SCC

// Any edge (C, C') in condensation graph comes from 
// a component with a larger value of tout to component with a smaller value.

// the resulting algorithm's scheme generates strongly connected components by decreasing order of their exit times,
// thus it generates components - vertices of condensation graph - in topological sort order.

// https://cses.fi/problemset/task/1683/

void solve()
{
  ll n, m; cin >> n >> m;
  vector<vector<ll>> adj(n);   
  vector<vector<ll>> radj(n);

  for (ll i = 0; i < m; i++)
  {
    ll x, y; cin >> x >> y;
    x--; y--;
    adj[x].push_back(y);
    radj[y].push_back(x); 
  }   

  vector<ll> vis(n, 0);
  vector<ll> order;

  function<void(ll)> dfs1 = [&](ll v)
  {
    vis[v] = 1;
    for (auto x: adj[v])
    {
      if (!vis[x])
        dfs1(x);
    }
    order.push_back(v);
  }; 

  for (ll i = 0; i < n; i++)
  {
    if (!vis[i])
      dfs1(i);
  }

  reverse(order.begin(), order.end());
  vis.assign(n, 0);
  vector<ll> scc;
  vector<vector<ll>> sccs; 

  function<void(ll)> dfs2 = [&](ll v)
  {
    vis[v] = 1;
    scc.push_back(v);
    for (auto x: radj[v])
    {
      if (!vis[x])
        dfs2(x);
    }
  }; 

  for (auto v: order)
  {
    if (!vis[v])
    {
      dfs2(v);
      sccs.push_back(scc);
      scc.clear(); 
    }
  }

  cout << sccs.size() << "\n";
  vector<ll> color(n);
  ll cnt = 1;

  for (auto v: sccs)
  {
    for (auto x: v)
      color[x] = cnt;
    cnt++;
  }

  for (auto x: color)
    cout << x << " ";
  cout << "\n";
}
// https://www.spoj.com/problems/TOPOSORT/
// Lexicographically smallest topological sort
// Khan's Algorithm

// Note: 
// A DAG G has at least one vertex with in-degree 0 and one vertex with out-degree 0
// So Pick all the vertices with in-degree as 0 and add them 
// into a queue (priority queue if needed lexicographically smallest)
// while removing it from the queue reduce indegree of neibhours

void solve()
{
  ll n, m; cin >> n >> m;
  vector<vector<ll>> adj(n);
  vector<ll> indegree(n, 0);

  for (ll i = 0; i < m; i++)
  {
    ll x, y; cin >> x >> y;
    x--; y--;
    adj[x].push_back(y); 
    indegree[y]++;
  }  

  vector<ll> topo;
  priority_queue<ll, vector<ll>, greater<ll>> q;

  for (ll i = 0; i < n; i++)
  {
    if (indegree[i] == 0)
      q.push(i);
  }

  while (!q.empty())
  {
    ll v = q.top();
    q.pop();
    topo.push_back(v);

    for (auto x: adj[v])
    {
      indegree[x]--;
      if (indegree[x] == 0)
        q.push(x);
    }
  }

  if ((ll) topo.size() < n)
    cout << "Sandro fails.";
  else
  {
    for (auto x: topo)
      cout << x + 1 << " ";
  }
}
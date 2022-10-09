struct UnionFind
{
  ll N, cc;
  vector<ll> parent, rank;

  UnionFind(ll n)
  {
    N = n;
    cc = N;
    rank.assign(N, 1);
    parent.assign(N, 0);
    iota(parent.begin(), parent.end(), 0);
  }

  ll find(ll x)
  {
    if (x == parent[x])
      return x;
    else
      return parent[x] = find(parent[x]);
  }

  void merge(ll x, ll y)
  {
    x = find(x);
    y = find(y);
    if (x != y)
    {
      if (rank[x] < rank[y])
        swap(x, y);
      parent[y] = x;
      rank[x] += rank[y];
      cc--;
    }
  }
};
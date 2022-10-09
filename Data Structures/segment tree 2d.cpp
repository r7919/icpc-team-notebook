// https://cses.fi/problemset/task/1739/
// this gives TLE due to O(C * log(n) * log(m)) update time
// optimal solution for invertible operations is BIT2D as it don't have const. C before log
 
struct SegTree
{
  SegTree *lChild, *rChild;
  ll l, r, val;
 
  SegTree(ll il, ll ir)
  {
    l = il, r = ir;
    if (l == r)
    {
      lChild = rChild = nullptr;
      val = 0;
      return;
    }
    ll mid = (l + r) / 2;
    lChild = new SegTree(l, mid);
    rChild = new SegTree(mid + 1, r);
    recalc();
  }
 
  SegTree(ll il, ll ir, vector<ll>& v)
  {
    l = il, r = ir;
    if (l == r)
    {
      lChild = rChild = nullptr;
      val = v[l];
      return;
    }
    ll mid = (l + r) / 2;
    lChild = new SegTree(l, mid, v);
    rChild = new SegTree(mid + 1, r, v);
    recalc();
  }
 
  void recalc()
  {
    if (l == r)
      return;
    else
      val = lChild->val + rChild->val;
  }
 
  ll rangeSum(ll ql, ll qr)
  {
    if (ql > r || qr < l)
      return 0ll;
    if (ql <= l && qr >= r)
      return val;
    return lChild->rangeSum(ql, qr) + rChild->rangeSum(ql, qr);
  }
 
  void pointUpdate(ll index, ll newVal)
  {
    if (l == r)
    {
      val = newVal;
      return;
    }
    if (index <= lChild->r)
      lChild->pointUpdate(index, newVal);
    else
      rChild->pointUpdate(index, newVal);
    recalc();
  }
 
  ~SegTree()
  {
    delete lChild;
    delete rChild;
  }
};
 
struct SegTree2D
{
  SegTree2D *lChild, *rChild;
  ll l, r;
  SegTree *d;
 
  SegTree2D(ll il, ll ir, vector<vector<ll>>& v, ll m)
  {
    l = il, r = ir;
    if (l == r)
    {
      lChild = rChild = nullptr;
      d = new SegTree(0, m - 1, v[l]);
      return;
    }
    ll mid = (l + r) / 2;
    lChild = new SegTree2D(l, mid, v, m);
    rChild = new SegTree2D(mid + 1, r, v, m);
    d = new SegTree(0, m - 1);
    merge(d, lChild->d, rChild->d);
  }
 
  void merge(SegTree *res, SegTree *a, SegTree *b)
  {
    if (!res)
      return;
    res->val = a->val + b->val;
    merge(res->lChild, a->lChild, b->lChild);
    merge(res->rChild, a->rChild, b->rChild);
  }
 
  ll rangeSum(ll x1, ll x2, ll y1, ll y2)
  {
    if (x1 > r || x2 < l)
      return 0ll;
    if (x1 <= l && x2 >= r)
      return d->rangeSum(y1, y2);
    return lChild->rangeSum(x1, x2, y1, y2) + rChild->rangeSum(x1, x2, y1, y2);
  }
 
  void pointMerge(SegTree *res, SegTree *a, SegTree *b, ll index)
  {
    if (!res)
      return;
    res->val = a->val + b->val;
    if ((res->lChild) && (index <= res->lChild->r))
      pointMerge(res->lChild, a->lChild, b->lChild, index);
    else
      pointMerge(res->rChild, a->rChild, b->rChild, index);
  }
 
  void pointUpdate(ll x, ll y, ll newVal)
  {
    if (l == r)
    {
      d->pointUpdate(y, newVal);
      return;
    }
    if (x <= lChild->r)
      lChild->pointUpdate(x, y, newVal);
    else
      rChild->pointUpdate(x, y, newVal);
    pointMerge(d, lChild->d, rChild->d, y);
  }
 
  ~SegTree2D()
  {
    delete lChild;
    delete rChild;
    delete d;
  }
};
 
void solve()
{
  ll n, q; cin >> n >> q; 
  vector<vector<ll>> v(n, vector<ll>(n));
  for (ll i = 0; i < n; i++)
  {
    string s; cin >> s;
    for (ll j = 0; j < n; j++)
      v[i][j] = (s[j] == '*'); 
  } 
 
  SegTree2D st(0, n - 1, v, n);
 
  for (ll i = 0; i < q; i++)
  {
    ll t; cin >> t;
    if (t == 1)
    {
      ll x, y; cin >> x >> y;
      x--; y--;
      v[x][y] = !v[x][y]; 
      st.pointUpdate(x, y, v[x][y]);
    }  
    else
    {
      ll x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      x1--; y1--; x2--; y2--;
      cout << st.rangeSum(x1, x2, y1, y2) << "\n"; 
    }
  }
}
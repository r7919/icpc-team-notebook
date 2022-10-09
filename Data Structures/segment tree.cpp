// version: point update range query [sum]

struct SegTree
{
  SegTree *lChild, *rChild;
  ll val, l, r;
 
  SegTree(ll il, ll ir, vector<ll>& v)
  {
    l = il, r = ir;
    if (l == r)
    {
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
    if (l != r)
    {
      delete lChild;
      delete rChild;
    }
  }
};




// version: range update range query [sum]

struct SegTree
{
  SegTree *lChild, *rChild;
  ll val, lazy, l, r, len;
 
  SegTree(ll il, ll ir, vector<ll>& v)
  {
    l = il, r = ir, lazy = 0;
    len = (r - l + 1);
    if (l == r)
    {
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
 
  void propagate() // correct this node and push lazy to childs
  {
    if (lazy != 0)
    {
      val += lazy * len;
      if (l != r)
      {
        lChild->lazy += lazy;
        rChild->lazy += lazy;
      }
      lazy = 0;
    }
  }
 
  void rangeUpdate(ll ql, ll qr, ll inc)
  {
    propagate();
    if (ql > r || qr < l)
      return;
    if (ql <= l && qr >= r)
    {
      lazy += inc;
      propagate();
      return;
    }
    lChild->rangeUpdate(ql, qr, inc);
    rChild->rangeUpdate(ql, qr, inc);
    recalc();
  }
 
  ll rangeSum(ll ql, ll qr)
  {
    propagate();
    if (ql > r || qr < l)
      return 0ll;
    if (ql <= l && qr >= r)
      return val;
    return lChild->rangeSum(ql, qr) + rChild->rangeSum(ql, qr);
  }
 
  ~SegTree()
  {
    if (l != r)
    {
      delete lChild;
      delete rChild;
    }
  }
};




// version: using node for more parameters 
// https://www.spoj.com/problems/GSS1/

struct node
{
  ll psum;
  ll ssum;
  ll tsum;
  ll mss;
 
  // Note: make sure that merge(node, default) == node
  node(ll a = -INF, ll b = -INF, ll c = 0, ll d = -INF)
  {
    psum = a;
    ssum = b;
    tsum = c;
    mss = d;
  }
};
 
struct SegTree
{
  SegTree *lChild, *rChild;
  ll l, r;
  node d;
 
  SegTree(ll il, ll ir, vector<ll>& v)
  {
    l = il, r = ir;
    if (l == r)
    {
      d = node(v[l], v[l], v[l], v[l]);
      return;
    }
    ll mid = (l + r) / 2;
    lChild = new SegTree(l, mid, v);
    rChild = new SegTree(mid + 1, r, v);
    d = merge(lChild->d, rChild->d);
  }
 
  node merge(node a, node b)
  {
    node res;
    res.psum = max(a.psum, a.tsum + b.psum);
    res.ssum = max(b.ssum, b.tsum + a.ssum);
    res.tsum = a.tsum + b.tsum;
    res.mss = max({a.mss, b.mss, a.ssum + b.psum});
    return res;
  }
 
  node rangeMss(ll ql, ll qr)
  {
    if (ql > r || qr < l)
      return node();
    if (ql <= l && qr >= r)
      return d;
    return merge(lChild->rangeMss(ql, qr), rChild->rangeMss(ql, qr));
  }
 
  void pointUpdate(ll index, ll newVal)
  {
    if (l == r)
    {
      d = node(newVal, newVal, newVal, newVal);
      return;
    }
 
    if (index <= lChild->r)
      lChild->pointUpdate(index, newVal);
    else
      rChild->pointUpdate(index, newVal);
 
    d = merge(lChild->d, rChild->d);
  }
 
  ~SegTree()
  {
    if (l != r)
    {
      delete lChild;
      delete rChild;
    }
  }
};
 
void solve()
{
  ll n, m; cin >> n;
  vector<ll> v(n);
 
  for (ll i = 0; i < n; i++)
    cin >> v[i];
 
  SegTree st(0, n - 1, v);
 
  cin >> m; 
 
  for (ll i = 0; i < m; i++)
  {
    ll x, y; cin >> x >> y;
    x--; y--;
    cout << st.rangeMss(x, y).mss << "\n"; 
  }
}
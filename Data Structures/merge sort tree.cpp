// we basically keep sorted vector at each node
// to find number of elements <= x in a range, we find it for all log(n) nodes and add up 
// Note: for updates use ordered set instead of vector

struct SegTree
{
  SegTree *lChild, *rChild;
  ll l, r, len;
  vector<ll> v;

  SegTree(ll il, ll ir, vector<ll>& iv)
  {
    l = il, r = ir;
    len = r - l + 1;
    v.resize(len);
    if (l == r)
    {
      v[0] = iv[l];
      return;
    }
    ll mid = (l + r) / 2;
    lChild = new SegTree(l, mid, iv);
    rChild = new SegTree(mid + 1, r, iv);
    merge(lChild->v.begin(), lChild->v.end(), rChild->v.begin(), rChild->v.end(), v.begin());
  } 

  // returns number of elements lesser-equal to x in [ql, qr]
  ll rangeLessEqualx(ll ql, ll qr, ll x)
  {
    if (ql > r || qr < l)
      return 0ll;
    if (ql <= l && qr >= r)
    {
      auto it = upper_bound(v.begin(), v.end(), x);
      return ll(it - v.begin());
    }
    return lChild->rangeLessEqualx(ql, qr, x) + rChild->rangeLessEqualx(ql, qr, x);
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
  ll n, Q; cin >> n >> Q;
  vector<ll> v(n);

  for (ll i = 0; i < n; i++)
    cin >> v[i];

  SegTree st(0, n - 1, v);  

  for (ll q = 0; q < Q; q++)
  {
    ll L, R, k;
    cin >> L >> R >> k;
    L--; R--;

    // kth smallest element in [L, R] 
    // binary search on ans
    ll l = 0, r = 1e10, ans = 1e10;
    while (l <= r)
    {
      ll mid = (l + r) / 2;
      if (st.rangeLessEqualx(L, R, mid) < k)
      {
        ans = mid;
        l = mid + 1;
      }
      else
        r = mid - 1;
    }

    cout << ans + 1 << "\n";
  }
}
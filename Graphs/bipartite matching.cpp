vvll g; vll mt; vector<bool> visited; ll cnt = 0;
bool try_kuhn(ll i){
    if (visited[i])
        return false;
    visited[i] = true;
    for (int to : g[i]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = i;
            return true;
        }
    }
    return false;
}

void solve(){
    ll n,m,k;
    cin>>n>>m>>k;
    g.resize(n+1); mt.assign(m+1,-1);
    for (ll i = 0; i < k; i++){
        ll a,b;
        cin>>a>>b;
        g[a].push_back(b);
    }
    for (ll i = 1; i <= n; i++){
        visited.assign(n+1,false);
        try_kuhn(i);
    }
    for (ll i = 1; i <= m; i++)
        if (mt[i] != -1)
            cnt++;
    printf("%lld\n",cnt);
    for (ll i = 1; i <= m; i++)
        if (mt[i] != -1)
            printf("%lld %lld\n", mt[i], i);
}

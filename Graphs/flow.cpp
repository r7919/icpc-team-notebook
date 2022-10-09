ll n,m;
ll g[505][505];
ll source, sink;
vector <bool> visited(505, false);
ll dfs(ll i, ll amount){
    if (i == sink)
        return amount;
    visited[i] = true;

    for (ll j = 1; j <= n; j++){
        if (g[i][j] > 0 && visited[j] == false){
            int sent =  dfs(j, min(amount, g[i][j]));
            if (sent > 0) {
                g[i][j] -= sent;
                g[j][i] += sent;
                return sent; 
            }
        }
    }
    return 0;
}

ll run(){
    ll total = 0;
    ll sent = -1;
    while (sent != 0) {
        visited.assign(n,false);
        sent = dfs(source, INT_MAX);
        total += sent;
    }
    return total;
}

void solve(){
    cin>>n>>m;
    source = 1, sink = n;
    visited.assign(n,false);
    for (ll i = 1; i <= n; i++)
        for (ll j = 0; j <= n; j++)
            g[i][j] = 0;
    for (ll i = 1; i <= m; i++){
        ll a,b,c;
        cin>>a>>b>>c;
        g[a][b] += c;
    }
    cout << run() <<"\n";
}
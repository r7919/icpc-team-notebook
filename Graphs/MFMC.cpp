ll n,m;
ll g[505][505];
ll orig[505][505];
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

void dfs2(int i){
    visited[i] = true;
    for (ll j = 1; j <= n; j++){
        if (g[i][j] > 0 && visited[j] == false){
            dfs2(j);
        }
    }
}


void solve(){
    cin>>n>>m;
    source = 1, sink = n;
    visited.assign(n,false);
    for (ll i = 1; i <= n; i++)
        for (ll j = 0; j <= n; j++)
            g[i][j] = 0, orig[i][j] = 0;
    for (ll i = 1; i <= m; i++){
        ll a,b;
        cin>>a>>b;
        g[a][b] += 1;
        g[b][a] += 1;
        orig[a][b] += 1;
        orig[b][a] += 1;
    }
    ll flow = run();
    cout<<flow<<"\n";
    visited.assign(n,false);
    dfs2(1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (visited[i] == true && visited[j] == false && orig[i][j] > 0)
                cout << i << " " << j << "\n";
}
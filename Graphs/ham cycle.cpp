vector<vector<bool>> g(1e5+1,vector<bool>(1e5+1,false));
ll n,m;
vll path(1e5,-1);
vector<bool> visited(1e5+1,false);
bool hamcycle(ll idx){
    if (idx == n)
        return g[path[n-1]][path[0]];
    for (ll i = 1; i <= n; i++){
        if (!visited[i] && g[path[idx-1]][i]){
            path[idx] = i;
            visited[i] = true;
            if (hamcycle(idx+1))
                return true;
            path[idx] = -1;
            visited[i] = false;
        }
    }
    return false;
}
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin>>n>>m;
    for (ll i = 1; i <= m; i++){
        ll a,b;
        cin>>a>>b;
        g[a][b] = g[b][a] = true;
    }
    
    path.resize(n);
    path[0] = 1; // starts at post office
    visited[1] = true;
    if (hamcycle(1)){
        for (ll i = 0; i < n; i++)
            cout<<path[i]<<" ";
        cout<<"1\n";
    }
    else
        cout<<"IMPOSSIBLE\n";
    return 0;
}
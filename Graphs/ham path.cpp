
vvll g;
ll n,m;
int main(){ // ham path from 1 to n
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin>>n>>m;
    g.resize(n+1);
    for (ll i = 1; i <= m; i++){
        ll a,b;
        cin>>a>>b;
        g[a].push_back(b);
    }
    ll dp[n+1][1<<n]; // in mask if ith bit is set then i+1 is in chosen subset (...,3,2,1,0)
    for (ll i = 0; i < n+1; i++)
        for (ll j = 0; j < (1<<n); j++)
            dp[i][j] = 0;
    dp[1][1] = 1;
    for (ll mask = 1; mask < (1<<n); mask++){
        //cout<<mask<<endl;
        if (mask>>(n-1)&1){ // stuff where n is in subset
            // if (mask != (1<<n)-1)
                continue;
        }
        for (ll j = 1; j <= n; j++){
            //cout<<"j = "<<j<<endl;
            if (mask>>(j-1) & 1){ // stuff where j is in subset
                for (ll k = 0; k < g[j].size(); k++){
                    //cout<<"seeing vertex "<<g[j][k]<<endl;
                    if (mask>>(g[j][k]-1) & 1)
                        continue;
                    dp[g[j][k]][mask ^ (1<<(g[j][k]-1))] = (dp[j][mask] + dp[g[j][k]][mask ^ (1<<(g[j][k]-1))])%MOD;
                }
            }
        }
    }
    cout<<dp[n][(1<<n)-1]%MOD<<"\n";
    return 0;
}
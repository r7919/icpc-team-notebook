ll n,m; // n ppl each 2 wishes regarding m toppings 
vvll g,grev;
vll visited,completetimes,vertexid;
ll id = 1;

void fillorder(ll x){
    visited[x] = 0;
    for (ll j = 0; j < g[x].size(); j++)
        if (visited[g[x][j]] == -1)
            fillorder(g[x][j]);
    visited[x] = 1;
    completetimes.push_back(x);
}

void dfs(ll x){
    visited[x] = 0;
    vertexid[x] = id;
    for (ll j = 0; j < grev[x].size(); j++)
        if (visited[grev[x][j]] == -1)
            dfs(grev[x][j]);
    visited[x] = 1;
}

int main(){
    //time_t start,end;
    //time(&start);
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin>>n>>m;
    g.resize(2*m+1);
    grev.resize(2*m+1);
    visited.resize(2*m+1);
    vertexid.resize(2*m+1);
    fill (visited.begin(), visited.end(), -1);
    // m toppings n conditions
    // 2*n edges, 2*m vertices
    // 1,2,3,...m => 1,-1,2,-2....m,-m => 1,2,3...2*m
    for (ll i = 1; i <= n; i++){
        char x,y;
        ll a,b;
        cin>>x; cin>>a; cin>>y; cin>>b;
        if (x == '+' && y == '+'){
            g[2*a].push_back(2*b-1);
            g[2*b].push_back(2*a-1);
            grev[2*b-1].push_back(2*a);
            grev[2*a-1].push_back(2*b);
        }
        if (x == '-' && y == '+'){
            g[2*a-1].push_back(2*b-1);
            g[2*b].push_back(2*a);
            grev[2*b-1].push_back(2*a-1);
            grev[2*a].push_back(2*b);
        }
        if (x == '+' && y == '-'){
            g[2*a].push_back(2*b);
            g[2*b-1].push_back(2*a-1);
            grev[2*b].push_back(2*a);
            grev[2*a-1].push_back(2*b-1);
        }
        if (x == '-' && y == '-'){
            g[2*a-1].push_back(2*b);
            g[2*b-1].push_back(2*a);
            grev[2*b].push_back(2*a-1);
            grev[2*a].push_back(2*b-1);
        }
    }
    for (ll i = 1; i <= 2*m; i++)
        if (visited[i] == -1)
            fillorder(i);
    fill (visited.begin(), visited.end(), -1);
    while (completetimes.size() != 0){
        ll temp = completetimes[completetimes.size()-1]; completetimes.pop_back();
        if (visited[temp] == -1){
            dfs(temp);
            id++;
        }
    }
    ll flag = 0;
    vector <char> ans(m+1);
    for (ll i = 1; i <= m; i++){
        if (vertexid[2*i-1] == vertexid[2*i])
            flag = 1;
        else if (vertexid[2*i-1] < vertexid[2*i])
            ans[i] = '-';
        else if (vertexid[2*i-1] > vertexid[2*i])
            ans[i] = '+';
    }
    if (flag == 0)
        for (ll i = 1; i <= m; i++)
            cout<<ans[i]<<" ";
    else 
        cout<<"IMPOSSIBLE\n";
    
    //time(&end);
    //double time_taken = double(end-start);
    //cout<<"\nTime taken for execution is "<< fixed << time_taken << setprecision(5)<<" sec\n";
    return 0;
}


vvll g;
ll n,m;
vll visited(1e5+1,-1);
vll degree(1e5+1,0);
stack <ll,vll> s;
vll answer;
void dfs(ll x){
    visited[x] = 1;
    for (ll j = 0; j < g[x].size(); j++){
        if (visited[g[x][j]] == -1)
            dfs(g[x][j]);
    }
}
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin>>n>>m;
    g.resize(n+1); visited.resize(n+1);
    for (ll i = 1; i <= m; i++){
        ll a,b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
        degree[a]++;
        degree[b]++;
    }
    dfs(1);
    for (ll i = 1; i <= n; i++){
        if (visited[i] == -1 && degree[i] != 0){
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
    }
    for (ll i = 1; i <= n; i++){
        if (degree[i] % 2 == 1){
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
    }
    s.push(1);
    while (!s.empty()){
        ll temp = s.top();
        if (degree[temp] == 0){
            answer.push_back(temp);
            s.pop();
        }
        else {
            degree[g[temp][0]]--;
            degree[temp]--;
            s.push(g[temp][0]);
            g[g[temp][0]].erase(find(g[g[temp][0]].begin(),g[g[temp][0]].end(),temp));
            g[temp].erase(g[temp].begin()); 
        }
    }
    for (ll j = 0; j < answer.size(); j++)
        cout<<answer[j]<<" ";
    cout<<"\n";
    return 0;
}

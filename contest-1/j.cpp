#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

const int A = 5e6 + 5;
bool p[A];

void Solve() 
{
    int n, m, s, t; cin >> n >> m >> s >> t;
    
    vector<vector<array<int, 3>>> adj(n + 1);
    for (int i = 1; i <= m; i++){
        int u, v, cap, w; cin >> u >> v >> cap >> w;
        
        adj[u].push_back({v, cap, w});
        // adj[v].push_back({u, cap, w});
    }
    
    int lo = 0, hi = 5e6;
    while (lo != hi){
        int mid = (lo + hi + 1) / 2;
        
        queue <int> q;
        q.push(s);
        vector <bool> vis(n + 1, false);
        vis[s] = true;
        
        while (!q.empty()){
            int u = q.front(); q.pop();
            
            for (auto [v, c, w] : adj[u]) if (c >= mid){
                if (!vis[v]){
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        
        if (vis[t]){
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    
    p[1] = true;
    for (int i = 2; i < A; i++) p[i] = true;
    for (int i = 2; i < A; i++) if (p[i]){
        for (int j = 2 * i; j < A; j += i){
            p[j] = false;
        }
    }
    
    if (lo == 0){
        cout << 0 << " " << 0 << "\n";
        return;
    }
    
    while (!p[lo]){
        lo--;
    }
    
    priority_queue <pair<int, int>> pq;
    vector <int> dp(n + 1, INF);
    dp[s] = 0;
    pq.push({-dp[s], s});
    
    while (!pq.empty()){
        auto pi = pq.top(); pq.pop();
        
        int d = -pi.first;
        int u = pi.second;
        if (dp[u] != d) continue;
        
        for (auto [v, c, w] : adj[u]) if (c >= lo){
            if (dp[v] > dp[u] + w){
                dp[v] = dp[u] + w;
                pq.push({-dp[v], v});
            }
        }
    }
    
    cout << lo << " " << (dp[t] * lo) << "\n";
}

int32_t main() 
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // freopen("in",  "r", stdin);
    // freopen("out", "w", stdout);
    
 //   cin >> t;
    for(int i = 1; i <= t; i++) 
    {
        //cout << "Case #" << i << ": ";
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}

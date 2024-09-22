#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

const int facN = 1e6 + 5;
const int mod = 1e9 + 7; // 998244353
int ff[facN], iff[facN];
bool facinit = false;

int power(int x, int y){
    if (y == 0) return 1;

    int v = power(x, y / 2);
    v = 1LL * v * v % mod;

    if (y & 1) return 1LL * v * x % mod;
    else return v;
}

void Solve() 
{
    int n; cin >> n;
    
    int ans = 0;
    
    vector<vector<int>> adj(n + 1);
    
    for (int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector <int> dp(n + 1, 0);
    
    auto dfs = [&](auto self, int u, int par) -> void{
        dp[u] = 1;
        
        for (int v : adj[u]) if (v != par){
            self(self, v, u);
            dp[u] += dp[v];
        }
        
        ans += dp[u] * (n - dp[u]);
    };
    dfs(dfs, 1, 0);
    
    ans %= mod;
    
    int v = n * (n + 1) / 2;
    v %= mod;
    
    ans *= power(v, mod - 2);
    ans %= mod;
    
    cout << ans << "\n";
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

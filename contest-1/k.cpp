#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n, q; cin >> n >> q;
    
    vector<array<int, 3>> a;
    for (int i = 0; i < n; i++){
        int c, m, t; cin >> c >> m >> t;
        
        a.push_back({t, c, m});
    }
    
    sort(a.begin(), a.end(), greater<array<int, 3>>());
    
    int p = 0;
    
    vector <array<int, 3>> b;
    for (int i = 0; i < q; i++){
        int m, k; cin >> m >> k;
        
        b.push_back({m, k, i});
    }
    
    sort(b.begin(), b.end(), greater<array<int, 3>>());
    
    const int A = 1e4 + 5;
    vector <int> dp(A, 0);
    vector <int> ans(q);
    
    for (auto [t, b, i] : b){
        while (p != a.size() && a[p][0] > t){
            int c = a[p][1];
            int m = a[p][2];
            p++;
            
            for (int j = A - 1; j >= m; j--){
                dp[j] = max(dp[j], dp[j - m] + c);
            }
        }
        
        ans[i] = dp[b];
    }
    
    for (auto x : ans){
        cout << x << "\n";
    }
}

int32_t main() 
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // freopen("in",  "r", stdin);
    // freopen("out", "w", stdout);
    
  //  cin >> t;
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

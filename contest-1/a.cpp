#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    // state is (i, matching suffix, last) 
    // brute over next => N * M * 10 
    // recalculate matching suffix fast 
    // precalculate
    
    int n, m, k; cin >> n >> m >> k;
    
    string s; cin >> s;
    
    vector<vector<int>> match(m + 1, vector<int>(10, 0));
    for (int i = 0; i <= m; i++){
        for (int j = 0; j < 10; j++){
            string t = "";
            for (int k = 0; k < i; k++) t += s[k];
            t += (char)('0' + j);
            
            for (int len = 1; len <= (int)t.size(); len++){
                bool good = true;
                int start = (int)t.size() - len;
                for (int k = 0; k < len; k++) if (t[start + k] != s[k]) good = false;
                
                if (good) match[i][j] = len;
            }
        }
    }
    
    vector<vector<int>> dp(m + 1, vector<int>(10, 0));
    dp[0][k]++;
    
    const int mod = 1e9 + 7;
    
    vector<vector<bool>> can(10, vector<bool>(10, false));
    
    // vector <pair<int, int>> pos(10);
    // for (int i = 1; i < 10; i++){
    //     pos[i].first = (i - 1) / 3;
    //     pos[i].second = (i - 1) % 3;
    // }
    // pos[0].first = 3;
    // pos[0].second = 1;
    
    // for (int i = 0; i < 10; i++){
    //     cout << pos[i].first << " " << pos[i].second << "\n";
    // }
    
    // for (int x = 0; x < 10; x++) for (int y = 0; y < 10; y++){
    //     int dx = abs(pos[x].first - pos[y].first);
    //     int dy = abs(pos[x].second - pos[y].second);
        
    //     if (dx > dy) swap(dx, dy);
        
    //     if (dx == 1 && dy == 2) can[x][y] = true;
    // }
    
    auto upd = [&](int x, int y){
        can[x][y] = true;  
        can[y][x] = true;
    };
    
    upd(1, 6);
    upd(1, 8);
    upd(2, 7);
    upd(2, 9);
    upd(3, 4);
    upd(3, 8);
    upd(4, 9);
    upd(4, 0);
    upd(6, 7);
    upd(6, 0);
    
    for (int i = 1; i <= n; i++){
        vector<vector<int>> ndp(m + 1, vector<int>(10, 0));
        for (int j = 0; j <= m; j++){
            for (int k = 0; k < 10; k++){
                for (int l = 0; l < 10; l++){
                    if (can[k][l]){
                        int nx = match[j][l];
                        
                        if (nx < m || m == 0){
                            ndp[nx][l] += dp[j][k];
                            if (ndp[nx][l] >= mod){
                                ndp[nx][l] -= mod;
                            }
                        }
                    }
                }
            }
        }
        
        dp = ndp;
    }
    
    int ans = 0;
    for (auto x : dp) for (auto y : x) ans += y;
    
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

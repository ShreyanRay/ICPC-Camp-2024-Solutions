#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n, m, k; cin >> n >> m >> k;
    
    vector <string> a(n);
    for (auto &x : a) cin >> x;
    
    
    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(m, vector<vector<int>>(k + 1, vector<int>(3, INF))));
    
    auto simulate = [&](int k, int piece){
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        vector<vector<pair<int, int>>> got(n * m);
        
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (a[i][j] != '#' && dp[i][j][k][piece] != INF){
            got[dp[i][j][k][piece]].push_back({i, j});
        }
        
        deque <pair<int, int>> q;
        
        auto add = [&](int x){
            if (got[x].size()){
                for (auto [y, z] : got[x]) if (!vis[y][z]){
                    vis[y][z] = true;
                    q.push_front({y, z});
                }
                got[x].clear();
            }  
        };
        
        add(0);
        
        deque <int> vec;
        for (int z = 0; z < n * m; z++){
            if (got[z].size()){
                vec.push_back(z);
            }
        }
        
        bool v2[n][m][5][5];
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                for (int k = 0; k < 5; k++){
                    for (int l = 0; l < 5; l++){
                        v2[i][j][k][l] = false;
                    }
                }
            }
        }
        
        while (!q.empty()){
            auto [x, y] = q[0];
            q.pop_front();
            int d = dp[x][y][k][piece];
            add(d);
            
            if (piece == 0){
                for (int dx = -1; dx <= 1; dx++){
                    for (int dy = -1; dy <= 1; dy++){
                        int nx = x + dx;
                        int ny = y + dy;
                        
                        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && a[nx][ny] != '#') {
                            vis[nx][ny] = true;
                            dp[nx][ny][k][piece] = d + 1;
                            q.push_back({nx, ny});
                        }
                    }
                }
            } else if (piece == 2){
            //    cout << "HERE " << x << " " << y << " " << d << '\n';
                for (int dx = -2; dx <= 2; dx++){
                    for (int dy = -2; dy <= 2; dy++){
                        int v1 = abs(dx);
                        int v2 = abs(dy);
                        if (min(v1, v2) != 1 || max(v1, v2) != 2) continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        
                        
                        
                        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && a[nx][ny] != '#'){
                           // cout << "UPD " << nx << " " << ny << " " << (d + 1) << "\n";
                            vis[nx][ny] = true;
                            dp[nx][ny][k][piece] = d + 1;
                            q.push_back({nx, ny});
                        }
                    }
                }
            } else {
                for (int dx = -1; dx <= 1; dx++){
                    for (int dy = -1; dy <= 1; dy++) if (dx != 0 || dy != 0){
                        for (int i = 1; ; i++){
                            int nx = x + dx * i;
                            int ny = y + dy * i;
                            
                            if (nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] != '#'){
                                if (v2[nx][ny][dx + 1][dy + 1]) break;
                                v2[nx][ny][dx + 1][dy + 1] = true;
                                if (!vis[nx][ny]){
                                    vis[nx][ny] = true;
                                    dp[nx][ny][k][piece] = d + 1;
                                    q.push_back({nx, ny});
                                }
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            
            if (q.empty()){
                while (q.empty() && vec.size()){
                    int ff = vec[0];
                    vec.pop_front();
                    add(ff);
                }
            }
        }
    };
    
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (a[i][j] == 'B') dp[i][j][0][0] = 0;
    
    simulate(0, 0);
    
    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < m; j++){
    //         cout << dp[i][j][0][0] << " \n"[j + 1 == m];
    //     }
    // }
    
    for (int kk = 1; kk <= k; kk++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                for (int p1 = 0; p1 < 3; p1++){
                    for (int p2 = 0; p2 < 3; p2++){
                        dp[i][j][kk][p1] = min(dp[i][j][kk][p1], dp[i][j][kk - 1][p2]);
                    }
                }
            }
        }
        
        simulate(kk, 1);
        simulate(kk, 2);
        // cout << '\n';
        
        // for (int i = 0; i < n; i++){
        //     for (int j = 0; j < m; j++){
        //         cout << dp[i][j][1][2] << " \n"[j + 1 == m];
        //     }
        // }
        
        // cout << '\n';
        
        // for (int i = 0; i < n; i++){
        //     for (int j = 0; j < m; j++){
        //         cout << dp[i][j][1][1] << " \n"[j + 1 == m];
        //     }
        // }
    }
    
    int ans = INF;
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i][j] == 'P'){
                for (int kk = 0; kk <= k; kk++){
                    ans = min(ans, dp[i][j][kk][0]);
                    ans = min(ans, dp[i][j][kk][1]);
                    ans = min(ans, dp[i][j][kk][2]);
                }
            }
        }
    }
    
    if (ans == INF) ans = -1;
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

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18
#define double long double

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n, m; cin >> n >> m;
    
    double eps = 1e-5;
    
    vector <pair<double, double>> a(n), b(m);
    for (auto &x : a){
        cin >> x.first >> x.second;
    }
    for (auto &x : b){
        cin >> x.first >> x.second;
    }
    
    auto dist = [&](pair <double, double> a, pair <double, double> b){
        double dx = abs(a.first - b.first);
        double dy = abs(a.second - b.second);
        
        double ans = sqrtl(dx * dx + dy * dy);
        return ans;
    };
    
    vector <double> da, db;
    for (int i = 1; i < n; i++){
        da.push_back(dist(a[i - 1], a[i]));
    }
    for (int i = 1; i < m; i++){
        db.push_back(dist(b[i - 1], b[i]));
    }
    
    int ans = 0;
    int pa = 0, pb = 0;
    while (pa < da.size() && pb < db.size()){
        double reduce = min(da[pa], db[pb]);
        da[pa] -= reduce;
        db[pb] -= reduce;
        
        int add = 0;
        
        if (da[pa] < eps){
            pa++;
        } else {
            add = 1;
        }
        
        if (db[pb] < eps){
            pb++;
        } else {
            add = 1;
        }
        
        if (add) ans++;
    }
    
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

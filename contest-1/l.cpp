#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    string s; cin >> s;
    
    int n = s.size();
    int a = 0, b = 0;
    vector <int> pa(n + 1), pb(n + 1);
    
    for (int i = 0; i < n; i++){
        if (s[i] == 'A'){
            pa[i + 1] = pa[i] + 1;
            pb[i + 1] = pb[i];
            a++;
        } else {
            pb[i + 1] = pb[i] + 1;
            pa[i + 1] = pa[i];
            b++;
        }
    }
    
    if ((a & 1) || (b & 1)){
        cout << "NO\n";
        return;
    }
    
    a /= 2;
    b /= 2;
    
    for (int i = 1; i <= n; i++){
        if (pa[n] - pa[i - 1] < a) continue;
        if (pb[n] - pb[i - 1] < b) continue;
        
        int lo = i, hi = n;
        while (lo != hi){
            int mid = (lo + hi) / 2;
            
            int v1 = pa[mid] - pa[i - 1];
            int v2 = pb[mid] - pb[i - 1];
            
            if (v1 < a || v2 < b){
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        
        if ((pa[lo] - pa[i - 1]) == a && (pb[lo] - pb[i - 1]) == b){
            cout << "YES\n";
            cout << i << " " << (lo + 1) << "\n";
            return;
        }
    }
    
    cout << "NO\n";
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

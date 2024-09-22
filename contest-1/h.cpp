#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int findSmallestI(int a, int b, int c) {
    int target = (-a % b + b) % b;

    int x, y;
    int gcd = extendedGCD(c, b, x, y);

    if (target % gcd != 0) {
        while (1);
    }
    x *= target / gcd;
    int mod = b / gcd;
    int i = (x % mod + mod) % mod;

    return i;
}

void Solve() 
{
    int x, y; cin >> x >> y;
    
    int n; cin >> n;
    
    vector <int> a(n), c(n, 0);
    int g = 0;
    for (auto &x : a) cin >> x, g = gcd(g, x);
    
    int diff = (x - y);
    vector <int> suff_gcd(n + 1, 0);
    for (int i = n - 1; i >= 0; i--){
        suff_gcd[i] = gcd(suff_gcd[i + 1], a[i]);
    }
    
    for (int i = 0; i < n; i++){
        if (diff % a[i] == 0){
            c[i] = -diff / a[i];
            break;
        }
        
        if (diff % suff_gcd[i + 1] == 0){
            continue;
        }
        
        // make diff divisible by suff_gcd[i + 1] 
        // diff + a[i] * x % suff_gcd[i + 1] 
        int x = findSmallestI(diff, suff_gcd[i + 1], a[i]);
        diff += x * a[i];
        c[i] = x;
        
        const int LIM = 1e9 * suff_gcd[i + 1];
        if (diff > LIM){
            int subt = lcm(a[i], suff_gcd[i + 1]);
            diff -= subt;
            c[i] -= subt / a[i];
        }
    }
    
    for (auto x : c){
        assert(-1e9 <= x);
        assert(x <= 1e9);
        
        if (x > 0){
            cout << x << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    
    for (auto x : c){
        if (x < 0){
            cout << -x << "\n";
        } else {
            cout << 0 << "\n";
        }
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

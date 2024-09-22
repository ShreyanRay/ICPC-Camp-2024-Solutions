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

void factorialinit(){
    facinit = true;
    ff[0] = iff[0] = 1;

    for (int i = 1; i < facN; i++){
        ff[i] = 1LL * ff[i - 1] * i % mod;
    }

    iff[facN - 1] = power(ff[facN - 1], mod - 2);
    for (int i = facN - 2; i >= 1; i--){
        iff[i] = 1LL * iff[i + 1] * (i + 1) % mod;
    }
}

int C(int n, int r){
    if (!facinit) factorialinit();

    if (n == r) return 1;

    if (r < 0 || r > n) return 0;
    return 1LL * ff[n] * iff[r] % mod * iff[n - r] % mod;
}

int P(int n, int r){
    if (!facinit) factorialinit();

    assert(0 <= r && r <= n);
    return 1LL * ff[n] * iff[n - r] % mod;
}

int Solutions(int n, int r){
    //solutions to x1 + ... + xn = r 
    //xi >= 0

    return C(n + r - 1, n - 1);
}

void Solve() 
{
    int n; cin >> n;
    
    factorialinit();
    int ans = 0;
    for (int i = 0; i <= n; i++){
        int v = ff[n] * iff[i];
        if (i & 1) ans -= v;
        else ans += v;
    }
    
    ans %= mod;
    if (ans < 0) ans += mod;
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

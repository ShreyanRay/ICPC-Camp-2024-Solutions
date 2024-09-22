#include <bits/stdc++.h>
using namespace std;
//#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

struct node{
    int nx[26];
    int cnt;
};

const int M = 2e6 + 5;
node a[M];
int ptr = 2;

void add(string &s, int i, int p){
    a[p].cnt++;
    
    if (i == (int)s.size()){
        return;
    }
    
    int v = s[i] - '0';
    if (a[p].nx[v] == -1){
        a[p].nx[v] = ptr++;
    }
    
    add(s, i + 1, a[p].nx[v]);
}

int query(string &s, int i, int p){
    if (i == (int)s.size()){
        return a[p].cnt;
    }
    
    int v = s[i] - '0';
    if (a[p].nx[v] == -1){
        return 0LL;
    }
    
    return query(s, i + 1, a[p].nx[v]);
}

void Solve() 
{
    int n, m; cin >> n >> m;
    
    for (int i = 0; i < M; i++){
        a[i].cnt = 0;
        for (int j = 0; j < 26; j++){
            a[i].nx[j] = -1;
        }
    }
    
    vector <int> a(26);
    int p = 0;
    for (int i = 2; i < 10; i++){
        int v = 3;
        if (i == 9 || i == 7) v = 4;
        
        while (v--){
            a[p++] = i;
        }
    }
    
    for (int i = 0; i < n; i++){
        string s; cin >> s;
        
        for (auto &x : s){
            x = (char)(a[x - 'a'] + '0');
        }
        
        add(s, 0, 1);
    }
    
    for (int i = 0; i < m; i++){
        string s; cin >> s;
        
        cout << query(s, 0, 1) << "\n";
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

#include <bits/stdc++.h>
using namespace std;
#define INF (int)1e18
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

struct ds{
    int root[251];  
    int sz[251];
};

int n, m, q;
const int M = 1e5 + 69;
ds a[4 * M];
pair <int, int> b[M];

int find(int i, int x){
    if (a[i].root[x] == x) return x;
    return a[i].root[x] = find(i, a[i].root[x]);
}

void uni(int i, int x, int y){
    x = find(i, x);
    y = find(i, y);
    
    if (x == y) return;
    if (a[i].sz[x] < a[i].sz[y]) swap(x, y);
    
    a[i].root[y] = x;
    a[i].sz[x] += a[i].sz[y];
}

void unite(int i, int j, int k){
    for (int l = 1; l <= n; l++){
        a[i].root[l] = l;
    }
    
    for (int l = 1; l <= n; l++){
        if (a[j].root[l] != l){
            uni(i, find(j, l), l);
        }
    }
    
    for (int l = 1; l <= n; l++){
        if (a[k].root[l] != l){
            uni(i, find(k, l), l);
        }
    }
}

void Build(int l, int r, int pos){
    if (l == r){
        for (int i = 1; i <= n; i++){
            a[pos].root[i] = i;
            a[pos].sz[i] = 1;
        }
        
        a[pos].root[b[l].first] = b[l].second;
        a[pos].sz[b[l].first] = 2;
        return;
    }
    
    int mid = (l + r) / 2;
    Build(l, mid, pos * 2);
    Build(mid + 1, r, pos * 2 + 1);
    
    unite(pos, pos * 2, pos * 2 + 1);
}

void upd(int l, int r, int pos, int qp){
    if (l == r){
        for (int i = 1; i <= n; i++){
            a[pos].root[i] = i;
            a[pos].sz[i] = 1;
        }
        
        a[pos].root[b[l].first] = b[l].second;
        a[pos].sz[b[l].first] = 2;
        return;
    }
    
    int mid = (l + r) / 2;
    
    if (qp <= mid) upd(l, mid, pos * 2, qp);
    else upd(mid + 1, r, pos * 2 + 1, qp);
    
    unite(pos, pos * 2, pos * 2 + 1);
}

int use1 = 4 * M - 1;
int use2 = 4 * M - 2;

void query(int l, int r, int pos, int ql, int qr){
    if (l >= ql && r <= qr){
        unite(use1, use2, pos);
        swap(use1, use2);
        return;
    } else if (l > qr || r < ql){
        return;
    }
    
    int mid = (l + r) / 2;
    
    query(l, mid, pos * 2, ql, qr);
    query(mid + 1, r, pos * 2 + 1, ql, qr);
}

void Solve() 
{
    cin >> n >> m >> q;
    
    for (int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        
        u++;
        v++;
        
        b[i] = make_pair(u, v);
    }
    
    Build(1, m, 1);
    
    vector <pair<int, int>> ok;
    ok.push_back({1, m});
    
    while (q--){
        int t; cin >> t;
        
        auto output = [&](bool flag = false, int u = -1, int v = -1){
            for (int i = 1; i <= n; i++){
                a[use2].root[i] = i;
                a[use2].sz[i] = 1;
            }
            
            for (auto [l, r] : ok){
                query(1, m, 1, l, r);
            }
            
            if (!flag){
                int v = 0;
                for (int i = 1; i <= n; i++) v += a[use2].root[i] == i;
                
                cout << v << "\n";
                return;
            }
            
            if (find(use2, u) == find(use2, v)){
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        };
        
        if (t == 1){
            int l, r; cin >> l >> r;
            l++;
            r++;
            
            ok.clear();
            ok.push_back({l, r});
            
            output();
        } else if (t == 2){
            int l, r; cin >> l >> r;
            l++;
            r++;
            
            ok.clear();
            if (l != 1) ok.push_back({1, l - 1});
            if (r != m) ok.push_back({r + 1, m});
            
            output();
        } else if (t == 3){
            int x, u, v; cin >> x >> u >> v;
            x++;
            u++;
            v++;
            
            b[x] = make_pair(u, v);
            upd(1, m, 1, x);
            
            output();
        } else {
            int u, v; cin >> u >> v;
            u++;
            v++;
            
            output(true, u, v);
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
    
//    cin >> t;
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

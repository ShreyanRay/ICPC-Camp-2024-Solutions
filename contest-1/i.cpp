#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

struct segtree{
    struct node{
        int x = 0;
 
        void apply(int l, int r, int y){
            x = y;
        }
    };
 
    int n;
    vector <node> seg;
 
    node unite(node a, node b){
        node res;
        res.x = max(a.x, b.x);
        return res;
    }
 
    void push(int l, int r, int pos){
        
    }
 
    void pull(int pos){
        seg[pos] = unite(seg[pos * 2], seg[pos * 2 + 1]);
    }
 
    void build(int l, int r, int pos){
        if (l == r){
            return;
        }
 
        int mid = (l + r) / 2;
        build(l, mid, pos * 2);
        build(mid + 1, r, pos * 2 + 1);
        pull(pos);
    }
 
    template<typename M>
    void build(int l, int r, int pos, vector<M> &v){
        if (l == r){
            seg[pos].apply(l, r, v[l]);
            return;
        }
 
        int mid = (l + r) / 2;
        build(l, mid, pos * 2, v);
        build(mid + 1, r, pos * 2 + 1, v);
        pull(pos);
    }
 
    node query(int l, int r, int pos, int ql, int qr){
        push(l, r, pos);
        if (l >= ql && r <= qr){
            return seg[pos];
        }
        
        int mid = (l + r) / 2;
        node res{};
        if (qr <= mid) res = query(l, mid, pos * 2, ql, qr);
        else if (ql > mid) res = query(mid + 1, r, pos * 2 + 1, ql, qr);
        else res = unite(query(l, mid, pos * 2, ql, qr), query(mid + 1, r, pos * 2 + 1, ql, qr));
        
        pull(pos);
        return res;
    }
 
    template <typename... M>
    void modify(int l, int r, int pos, int ql, int qr, M&... v){
        push(l, r, pos);
        if (l >= ql && r <= qr){
            seg[pos].apply(l, r, v...);
            return;
        }
 
        int mid = (l + r) / 2;
        if (ql <= mid) modify(l, mid, pos * 2, ql, qr, v...);
        if (qr > mid) modify(mid + 1, r, pos * 2 + 1, ql, qr, v...);
 
        pull(pos);
    }
 
    segtree (int _n){
        n = _n;
        seg.resize(4 * n + 1);
        build(1, n, 1);
    }
 
    template <typename M>
    segtree (int _n, vector<M> &v){
        n = _n;
        seg.resize(4 * n + 1);
        if (v.size() == n){
            v.insert(v.begin(), M());
        }
        build(1, n, 1, v);
    }
 
    node query(int l, int r){
        return query(1, n, 1, l, r);
    }
 
    node query(int x){
        return query(1, n, 1, x, x);
    }
 
    template <typename... M>
    void modify(int ql, int qr, M&...v){
        modify(1, n, 1, ql, qr, v...);
    }
};

void Solve() 
{
    int n; cin >> n;
    
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    
    vector <int> b(n + 1);
    for (int i = 1; i < n; i++){
        b[i] = abs(a[i + 1] - a[i]);
    }
    
    segtree seg(n, b);
    
    int q; cin >> q;
    
    while (q--){
        int t; cin >> t;
        int x, y; cin >> x >> y;
        
        if (t == 1){
            a[x] = y;
            
            if (x > 1){
                b[x - 1] = abs(a[x] - a[x - 1]);
                seg.modify(x - 1, x - 1, b[x - 1]);
            }
            if (x < n){
                b[x] = abs(a[x + 1] - a[x]);
                seg.modify(x, x, b[x]);
            }
        } else {
            int lo = x, hi = n;
            while (lo != hi){
                int mid = (lo + hi + 1) / 2;
                
                int v = seg.query(lo, mid - 1).x;
                if (v <= y) lo = mid;
                else hi = mid - 1;
            }
            
            cout << lo << "\n";
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

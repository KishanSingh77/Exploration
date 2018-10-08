#include <bits/stdc++.h>
#define Rd(r) freopen(r, "r", stdin)
#define Wt(w) freopen(w, "w", stdout)
#define deb(x) cerr << "DEBUG: "<< #x << " = " << x << endl;
#define endl '\n'

const int INF = 1e9+1;
const double PI = acos(-1.0);
const double EPS = 1e-9;
typedef long long LL;
using namespace std;

template <class T> void deb_array(T *arr, int length) {
    for (int i = 0; i < length; i++) {
        cout << arr[i] << ' ';
    } cout << '\n';
}

struct pp {
    int v, w;
    bool operator < (pp const &a) const {
        return w > a.w;
    }
};

void deb_vector(vector<pp> &v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << "(" << v[i].v << ' ' << v[i].w << ")";
    }
    cout << "]" << endl;
}


const int maxn = 1e4 + 5;
const int inf = 1e9 + 5;
int n, k, m; 
vector<pp> graph[maxn];

void deb_graph() {
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << " [";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << "(" << graph[i][j].v << "," << graph[i][j].w << ")" << (j == graph[i].size() - 1 ? "" : ", ");   
        }
        cout << "]" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    //deb_graph();

    priority_queue<pp> pq;
    vector<int> dist(n + 1, inf);
    pq.push({1, 0});
    dist[1] = 0;
    while (!pq.empty()) {
        int u = pq.top().v;
        int du = pq.top().w;
        pq.pop(); 
        if (du > dist[u]) {
            continue; 
        }
        /* if (u == n) {
            cout << dist[u] << endl;
            return 0;
        } */
        for (auto node : graph[u]) {
            int v = node.v;
            int w = node.w;
            if ((dist[u] / k) % 2 == 1) {
                w  = w + (((dist[u] / k) + 1) * k - dist[u]);
            } 
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({v, dist[v]});
            }
        }
    }
    cout << dist[n] << endl;
}


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
    int u, v;
    bool operator < (pp const &a) const {
        if (u < a.u) return true;
        if (a.u == u) return v > a.v;
        return false;
    }
};

void deb_vector(vector<pp> &v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << "(" << v[i].u << ' ' << v[i].v << ")";
    }
    cout << "]" << endl;
}


int main() {
    ios_base::sync_with_stdio(0);
    map<char, int> mp;
    mp['a'] = 5;
    cout << mp['b'] << endl;
}


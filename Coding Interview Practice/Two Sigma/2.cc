/*
ID: j316chuck
PROG:
LANG: C++
*/

#include <iostream>
#include <vector>
#include <map>
#include <set>
#define Rd(r) freopen(r, "r", stdin)
#define Wt(w) freopen(w, "w", stdout)
#define deb(x) cerr << "DEBUG: "<< #x << " = " << x << endl;
#define endl '\n'

const int INF = 1e9+1;
const double EPS = 1e-9;
typedef long long LL;
using namespace std;


const int maxn = 23;
const int maxm = 1 << maxn;

struct pp {
    int nr[2], ind;
    bool operator < (const pp &a) const {
        return a.nr[0] == nr[0] ? nr[1] < a.nr[1] : nr[0] < a.nr[0];
    }
} L[maxm];

int P[maxn][maxm];
int SA[maxm];
int n, stp;
string s, t;

void construct_suffix_array(string &str) {
    n = str.size();
    memset(P, -1, sizeof(P));
    memset(SA, 0, sizeof(SA));
    for (int i = 0; i < n; i++) {
        P[0][i] = str[i] - 'a';
    }
    stp = 0;
    for (int i = 1; (1 << stp) < n; i++, stp++) {
        for (int j = 0; j < n; j++) {
            L[j].ind = j;
            L[j].nr[0] = P[i - 1][j];
            L[j].nr[1] = j + (1 << stp) < n ? P[i - 1][j + (1 << stp)] : -1;
        }
        sort(L, L + n);
        for (int j = 0; j < n; j++) {
            P[i][L[j].ind] = j > 0 && L[j].nr[0] == L[j - 1].nr[0] && L[j].nr[1] == L[j - 1].nr[1] ? P[i][L[j - 1].ind]: j;
        }
    }
    if (n == 1) {
        P[0][0] = 0;
        stp = 1;
    }
    stp--;
    for (int j = 0; j < n; j++) {
        SA[j] = P[stp][j];
    }
}

int LCP(int i, int j) {
    if (i == j) return n - j;
    int ret = 0;
    for (int x = stp; x >= 0; x--) {
        if (i + (1 << x) <= n && j + (1 << x) <= n && P[x][i] == P[x][j]) {
            ret += (1 << x);
            i += (1 << x);
            j += (1 << x);
        }
    }
    return ret;
}

void sub_string(string &s) {
    int m = s.size();
    int cut_off_index = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (s[i] != 'a' && s[i] != 'o' && s[i] != 'u' && s[i] != 'e' && s[i] != 'i') {
            cut_off_index = i;
            break;
        }
    }
    string cut_off_str = s.substr(0, cut_off_index + 1);

    construct_suffix_array(cut_off_str);
    for (int i = 0; i < n; i++) {
        int c = L[i].ind;
        if (s[c] == 'a' || s[c] == 'i' || s[c] == 'o' || s[c] == 'u' || s[c] == 'e') {
            for (int j = c; j < m; j++) {
                if (s[j] != 'a' && s[j] != 'o' && s[j] != 'u' && s[j] != 'e' && s[j] != 'i') {
                    cout << s[j] << endl;
                    break;
                }
                cout << s[j];
            }
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int c = L[i].ind;
        if (s[c] == 'a' || s[c] == 'i' || s[c] == 'o' || s[c] == 'u' || s[c] == 'e') {
            cout << s.substr(c) << endl;
            break;
        }
    }
}


int main() {
    Rd("input.in");
    ios_base::sync_with_stdio(0);
    cin >> s;
    sub_string(s);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int maxm = 1e6 + 5;
const long long mod = 1e9 + 7;
int t, n; 
vector<int> prime_factors[maxm];
bool is_prime[maxm];
int parent[maxm];

void deb_array(vector<int> &v) {
	cout << '[';
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << (i == v.size() - 1 ? "" : ", "); 
	}
	cout << "]\n";
}

void make_set() {
	for (int i = 0; i < maxm; i++) {
		parent[i] = i;
	}
}

int getf(int x) {
	if (parent[x] == x) return x;
	return parent[x] = getf(parent[x]);
}

bool union_find(int x, int y) {
	int px = getf(x);
	int py = getf(y);
	if (px != py) {
		parent[px] = parent[py];
		return true;
	}
	return false; 
}


void sieve() {
	for (int i = 0; i < maxm; i++) is_prime[i] = true; 
	for (int i = 2; i < maxm; i++) {
		if (is_prime[i]) {
			prime_factors[i].push_back(i);
			for (int j = 2 * i; j < maxm; j += i) {
				prime_factors[j].push_back(i);
				is_prime[j] = false; 
			}
		} 
	}
}


long long exp(long long base, long long exponent) {
	if (exponent == 1) return base;
	long long a = exp(base, exponent / 2);
	a = a * a % mod; 
	long long mult = (exponent % 2 == 1 ? base : 1);
	return a * mult % mod; 
}

long long solve(vector<int> &v) {
	make_set();
	int groups = 0;
	bool seen[maxm] = {0};
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == 1) {
			groups += 1;
			continue;
		}
		for (int j = 0; j < prime_factors[v[i]].size(); j++) {
			int prime_factor = prime_factors[v[i]][j];
			if (!seen[prime_factor]) {
				seen[prime_factor] = true;
				groups += 1;
			}
		}
	}
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == 1) continue;
		for (int j = 1; j < prime_factors[v[i]].size(); j++) {
			int prime_factor_x = prime_factors[v[i]][j];
			int prime_factor_y = prime_factors[v[i]][j - 1];
 			if (union_find(prime_factor_x, prime_factor_y)) {
 				groups--;
			}
		}
	}
	long long answer = 1;
	for (int i = 0; i < groups; i ++) {
		answer = answer * 2 % mod;
	}
	answer = (answer - 2 + mod) % mod;
	return answer;
}

int main() {
	cin >> t;
	sieve();
	long long total = 0;
  	for (int i = 0; i < t; i++) {
  		cin >> n;
  		vector<int> a(n);
  		for (int i = 0; i < n; i++) {
  			cin >> a[i];
  		}
  		cout << solve(a) << endl;
  	}  
}

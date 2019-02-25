#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int sum; 
    cin >> sum;
    sort(arr.begin(), arr.end());
    long long ways = 0;
    for (int i = 0; i < n - 2; i++) {
        int target_sum = sum - arr[i];
        int l = i + 1, r = n - 1;
        cout << ways << ' ' << i << endl;
        while (l < r) {
            if (arr[l] == arr[r]) {
                if (arr[l] + arr[r] == target_sum) {
                    int elements_between = r - l + 1;
                    ways = ways + ((elements_between) * (elements_between - 1) / 2);
                }
                break; 
            } else if (arr[l] + arr[r] == target_sum) {
                int left_count = 1;
                while (arr[l + left_count] == arr[l]) {
                    left_count++;
                }
                int right_count = 1;
                while (arr[r - right_count] == arr[r]) {
                    right_count++;
                }
                l = l + left_count; 
                r = r - right_count;
                ways += left_count * right_count; 
            } else if (arr[l] + arr[r] < target_sum) {
                l++;
            } else if (arr[l] + arr[r] > target_sum) {
                r--;
            } else {
                cerr << "Missed Condition Somewhere in Code" << endl;
            }
        }
    }
    cout << ways << endl;
    return 0;
}


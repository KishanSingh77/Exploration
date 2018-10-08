#include <bits/stdc++.h>
using namespace std;
	
int L, W, frog_start_h, frog_start_w;
string moves;
vector<int> start;
vector<int> interval;
vector<int> speed;

int main() {
	cin >> L >> W;
	start.resize(L); interval.resize(L); speed.resize(L);
	for (int i = 0; i < L; i++) {
		cin >> start[i] >> interval[i] >> speed[i];
	}	  	
	reverse(start.begin(), start.end());
	reverse(interval.begin(), interval.end());
	reverse(speed.begin(), speed.end());

	vector< vector<int> > car_positions; 
	for (int i = 0; i < L; i++) {
		vector<int> v;
		if (i % 2 == 0) {
			for (int j = start[i]; j < W; j += interval[i]) {
				v.push_back(j);
			}
		} else {
			for (int j = W - 1 - start[i]; j >= 0; j -= interval[i]) {
				v.push_back(j);
			}
		}
		car_positions.push_back(v);
	}

	/*for (int i = 0; i < car_positions.size(); i++) {
		for (int j = 0; j < car_positions[i].size(); j++) {
			cout << car_positions[i][j] << ' ';
		} cout << endl;
	}*/
	cin >> frog_start_w >> moves;
	frog_start_h = -1;
	for (int i = 0; i < moves.size(); i++) {
		if (moves[i] == 'U') {
			frog_start_h += 1;
		} else if (moves[i] == 'D') {
			frog_start_h -= 1;
		} else if (moves[i] == 'R') {
			frog_start_w += 1;
		} else if (moves[i] == 'L') {
			frog_start_w -= 1;
		}
		//cout << "Frog position: " << frog_start_h << "," << frog_start_w << endl;
		if (frog_start_h == L) {
			break;
		}
		//update positions 
		bool squish[200][200] = { {false} };
		vector< vector<int> > new_car_positions; 
		for (int j = 0; j < L; j++) {
			vector<int> v;
			if (j % 2 == 0) {
				for (int k = 0; k < car_positions[j].size(); k++) {
					if (car_positions[j][k] + speed[j] >= W) {
						continue;
					} else {
						v.push_back(car_positions[j][k] + speed[j]);
						for (int l = car_positions[j][k] + 1; l <= car_positions[j][k] + speed[j]; l++) {
							squish[j][l] = true;
						}
					}
				}
				while (v[0] - interval[j] >= 0) {
					v.insert(v.begin(), v[0] - interval[j]);
					for (int l1 = v[0], l2 = 0; l1 >= 0 && l2 < speed[j]; l1--, l2++) {
						squish[j][l1] = true;
					}
				}
			} else {
				for (int k = 0; k < car_positions[j].size(); k++) {
					if (car_positions[j][k] - speed[j] < 0) {
						continue;
					} else {
						v.push_back(car_positions[j][k] - speed[j]);
						for (int l = car_positions[j][k] - 1; l >= car_positions[j][k] - speed[j]; l--) {
							squish[j][l] = true;
						}
					}
				}
				while (v[0] + interval[j] < W) {
					v.insert(v.begin(), v[0] + interval[j]);
					for (int l1 = v[0], l2 = 0; l1 < W && l2 < speed[j]; l1++, l2++) {
						squish[j][l1] = true;
					}
				}

			}
			/*for (int i = 0; i < v.size(); i++) {
				cout << v[i] << ' ';
			} cout << endl;*/
			new_car_positions.push_back(v);
		}


		if (frog_start_h != -1) {
			if (squish[frog_start_h][frog_start_w]) {
				cout << "squish" << endl;
				return 0;
			}
		}
		car_positions = new_car_positions;
	}
	if (frog_start_h < L) {
		cout << "squish" << endl;
		return 0;
	}
	cout << "safe" << endl;
	return 0;
}

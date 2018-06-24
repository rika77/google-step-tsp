#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define rep(i,n) FOR(i,0,n)
#define N 8
typedef long long ll;
typedef pair<float,float> P;	// Coordinate
vector<P> C;	// Cities
// first_step: all_search
// float or double ?
float cal_len(vector<int> order){
	// if salesman travels in this order, how long does it takes ?
	float len = 0.0;
	for (int i = 0; i < N - 1; i++){		
		float x0 = C[order[i]].first;
		float y0 = C[order[i]].second;
		float x1 = C[order[i + 1]].first;
		float y1 = C[order[i + 1]].second;

		len += sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0));
	}
	float x0 = C[order[N - 1]].first;
	float y0 = C[order[N - 1]].second;
	float x1 = C[order[0]].first;
	float y1 = C[order[0]].second;

	len += sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0));

	return len;
}

int main(){
	// skip over "x,y"
	string firstline;
	cin >> firstline;
	
	// put x,y in "C (Cities)"
	for (int i = 0; i < N; i++){
		float x,y;
		scanf("%f,%f", &x, &y);
		C.push_back(P(x,y));
	}

	// all enumuration
	vector<int> order(N);
	vector<int> mini_order(N);
	float mini_len = FLT_MAX;
	iota(order.begin(), order.end(), 0);

	do {
		// order is "0 1 2 3 4", "0 1 2 4 3", ... ,"4 3 2 1 0"
		float len = cal_len(order);
		if (len < mini_len){
			// update mini
			mini_len = len;
			mini_order = order;
		}

	} while (next_permutation(order.begin(), order.end()));
	// output
	cout << "index" << endl;
	for (auto num: mini_order) {
		cout << num << endl;
	}
	
	// cout << mini_len << endl;
	return 0;
}


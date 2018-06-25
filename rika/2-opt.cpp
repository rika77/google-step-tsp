#include<bits/stdc++.h>
using namespace std;
#define INF 999999.0
#define N 2048
typedef pair<float,float> P;
vector<P> data(N);
float dis[N][N];
bool visited[N] = {};
vector<int> trip;

void make_distance(vector<P> data) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				dis[i][j] = INF;	
			}
			else {
				float x0 = data[i].first;
				float x1 = data[j].first;
				float y0 = data[i].second;
				float y1 = data[j].second;
				dis[i][j] = sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0));
			}
		}
	}
}

float cal_total_len(vector<int> trip) {

	float len = 0.0;
	
	for (int i = 0; i < N - 1; i++) {
		len += dis[trip[i]][trip[i+1]];
	}
	len += dis[trip[N - 1]][trip[0]];

	return len;
}

int find_min(int k) {

	float min_length = INF;
	int min_city = k;

	for (int i = 0; i < N; i++) {
		if (!visited[i] && min_length > dis[k][i]) {
			min_length = dis[k][i];
			min_city = i;
		}
	}

	return min_city;
}

void two_opt() {
	for(int i = 0; i < N - 3; i++) {
		for (int k = i + 2; k < N - 1; k++) {
			int j = i + 1;
			int l = k + 1;
			if (dis[trip[i]][trip[j]] + dis[trip[k]][trip[l]] > dis[trip[i]][trip[k]] + dis[trip[j]][trip[l]]) {
				// float be = cal_total_len(trip);
				reverse(trip.begin() + j, trip.begin() + l);
				// float af = cal_total_len(trip);
				// cout << i << " " << j << " " << k << " " << l << endl;
				// cout  << be << " -> " << af << endl;
			}
		}
	}
}





int main() {

	//skip over "x,y"
    string firstline;
    cin >> firstline;
    
    //Input data
    for(int i = 0; i < N; i++) {
		float a,b;
        scanf("%f,%f", &a, &b);
        data[i].first=a;
        data[i].second=b;
    }

	make_distance(data);

	trip.push_back(0);
	visited[0] = 1;
	int next_city = find_min(0);

	// first: nearest neighbor
	for (int i = 0; i < N - 1; i++) {
		trip.push_back(next_city);
		visited[next_city] = 1;
    	next_city = find_min(next_city);
	}

	// second: 2-opt (swap)
	two_opt();


	for (auto num : trip) {
		cout << num << endl;
	}

	float min_len = cal_total_len(trip);
	cout << setprecision(10) << min_len << endl;
    return 0;
}

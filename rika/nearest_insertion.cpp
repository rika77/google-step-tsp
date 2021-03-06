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

void find_min_and_insert() {

	int size = trip.size();
	
	if (size == N) {
		// all cities have been visited !
		return;
	}

	float min_length = INF;
	// int from = -1;
	int to = -1; 
	int from_point = -1;	// trip中のどこか。insertionに必要
	// find_min
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[j] && min_length > dis[trip[i]][j]) {
			min_length = dis[trip[i]][j];
			// from = trip[i];
			from_point = i;
			to = j;
			}
		}
	}
	// insert
	trip.insert(trip.begin() + from_point, to);
	visited[to] = 1;

}

float cal_total_len(vector<int> trip) {

	float len = 0.0;
	/*
	for (auto num : trip) {
		len += dis[num][num + 1];
	}
	*/

	for (int i = 0; i < N - 1; i++) {
		len += dis[trip[i]][trip[i+1]];
	}

	// from end to start
	len += dis[trip[N - 1]][trip[0]];

	return len;
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
	
	while(trip.size() < N) {
		find_min_and_insert();
	}

	for (auto num : trip) {
		cout << num << endl;
	}

	float min_len = cal_total_len(trip);
	cout << setprecision(10) << min_len << endl;
    return 0;
}

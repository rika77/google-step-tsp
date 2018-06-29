#include<bits/stdc++.h>
using namespace std;
#define INF 999999.0
#define N 512
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

float di(int from, int to) {
	// distance betweeen trip(a) and trip(b)
	return dis[trip[from]][trip[to]];
}

void swap(int i, int j) {
	reverse(trip.begin() + i, trip.begin() + j);
	return;
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

	// 枝の選び方に改善の余地あり？
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

void three_opt() {

	// 枝の選び方に改善の余地あり？
	for(int a = 0; a < N - 5; a++) {
		for (int c = a + 2; c < N - 3; c++) {
			for (int e = c + 2; e < N - 1; e++) {
				int b = a + 1;
				int d = c + 1;
				int f = e + 1;

				float cases[8];
				cases[0] = di(a,b) + di(c,d) + di(e,f);
				cases[1] = di(a,c) + di(b,d) + di(e,f);
				cases[2] = di(a,b) + di(c,e) + di(d,f);
				cases[3] = di(a,e) + di(b,f) + di(c,d);
				cases[4] = di(a,d) + di(b,f) + di(c,e);
				cases[5] = di(a,e) + di(b,d) + di(c,f);
				cases[6] = di(a,c) + di(b,e) + di(d,f);
				cases[7] = di(a,d) + di(b,e) + di(c,f);

				float min_three = cases[0];
				int num = 0;
				for (int i = 1; i < 8; i++) {
					if (min_three > cases[i]) {
						min_three = cases[i];
						num = i;
					}
				}
				
				//float be = cal_total_len(trip);

				switch (num) {
					case 0:
						break;
					case 1:
						swap(b,c+1);
						break;
					case 2:
						swap(d,e+1);
						break;
					case 3:
						swap(b,e+1);
						break;
					case 4:
						swap(b,e+1);
						swap(e,d+1);
						break;
					case 5:
						swap(b,e+1);
						swap(c,b+1);
						break;
					case 6:
						swap(b,c+1);
						swap(d,e+1);
						break;
					case 7:
						swap(b,e+1);
						swap(e,d+1);
						swap(c,b+1);
						break;
				}

				//float af = cal_total_len(trip);
				// cout << i << " " << j << " " << k << " " << l << endl;
				//if (num) cout  << num << " " << be << " -> " << af << endl;
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

	two_opt();
	// second: 3-opt
	three_opt();


	for (auto num : trip) {
		cout << num << endl;
	}

	float min_len = cal_total_len(trip);
	cout << setprecision(10) << min_len << endl;
    return 0;
}

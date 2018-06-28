#include<bits/stdc++.h>
using namespace std;
#define INF 999999.9
#define N 16
typedef pair<float,float> P;
vector<P > data(N+1);
float dis[N][N];
float dp[1<<N][N];

void make_distance(vector<P> data) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				dis[i][j] = INF;	// is it ok ? inf ?
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

float TSP(int S, int v) {
    if(dp[S][v] >= 0.0){
        return dp[S][v];
    }
    if(S==(1<<N)-1 && v==0){
        return dp[S][v] = 0.0;
    }
    float dn=INF;
    for(int k=0; k<N; k++){
        if(!(S>>k & 1)){
			dn = min(dn, TSP(S|1<<k,k)+dis[v][k]);
        }
    }
    dp[S][v]=dn;
    return dp[S][v];
}

int main() {
    //int m;
    vector<int> ans;
	//skip over "x,y"
    string firstline;
    cin >> firstline;
    
    //Input data
    for(int i=0; i<N; i++) {
		float a,b; 
        scanf("%f,%f", &a, &b);
        data[i].first=a;
        data[i].second=b;
    }

	make_distance(data);
    //Fill (-1)
    for(int i=0; i<(1<<N);i++){
        for(int j=0; j<N; j++){
            dp[i][j]= -1.1;
        }
    }
    // run TSP
    cout << TSP(0,0) << endl;
/*
	for (int i=0;i<(1<<N);i++) {
		for (int j=0;j<N;j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	*/
    return 0;
}

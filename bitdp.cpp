#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
#define INF 999999

const int MAXN=16;
int n;
vector<pair<float,float> > data(MAXN+1);
float dp[1<<MAXN][MAXN];

int TSP(int S, int v) {
    if(dp[S][v] >= 0){
        return dp[S][v];
    }
    if(S==(1<<n)-1 && v==0){
        return dp[S][v]=0;
    }
    float dn=INF;
    for(int k=0; k<n; k++){
        if(!(S>>k & 1)){
            float x = data[v].first-data[k].first;
            x*=x;
            float y = data[v].second-data[k].second;
            y*=y;
            dn=min(dn, TSP(S|1<<k,k)+sqrt(x+y));
        }
    }
    dp[S][v]=dn;
    return dp[S][v];
}

int main() {
    int m;
    vector<int> ans;
    string firstline;
    cin>>firstline;
    
    //Fill INF
    for(int i=0; i<n; i++){
        data[i].first=INF;
        data[i].second=INF;
    }
    //Input data
    for(int i=0; i<m; i++) {
        float a,b; 
        cin>>a>>b; 
        data[i].first=a;
        data[i].second=b;
    }
    //Fill (-1)
    for(int i=0; i<(1<<MAXN);i++){
        for(int j=0; j<MAXN; j++){
            dp[i][j]=-1;
        }
    }
    // run TSP
    cout << TSP(0,0) << endl;
    return 0;
}
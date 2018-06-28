#include<bits/stdc++.h>
using namespace std;
#define INF 999999.0
#define N 8
typedef pair<float,float> P;
vector<P> data(N);		//x,y
bool visited[N] = {};	
vector<int> adj_MST[N];
bool visited_mst[N] = {};
vector<int> pre_trip;
vector<int> trip;
bool visited_sub[N] = {};
float dis[N][N];

struct UnionFind {
	
	// root[i]: i is belong to a tree whose root is root[i]
	vector<int> root; 
	// nodes[i] : how many nodes the tree has ? (i is belong to that tree)
	vector<int> nodes;

	UnionFind(int n) : root(n), nodes(n, 1) {
		// initialize. all nodes are separate.
		for (int i = 0; i < N; i++) {
			root[i] = i;
		}
	}

	// find the tree which x is belong to
	int find_root(int x) {
		if (x == root[x]) {
			return x;
		}
		else {
			return root[x] = find_root(root[x]);
		}
	}

	// merge x's tree (x is belong to) and y's tree (y is belong to)
	void unite_tree(int x, int y) {
		x = find_root(x);
		y = find_root(y);

		// if already x and y are in the same tree, as it is(not merge).
		if (x == y) {
			return;
		}

		// make x's tree > y's tree
		if (nodes[x] < nodes[y]) {
			swap(x,y);
		}

		// make "y's tree's root" x
		root[y] = x;
		nodes[x] += nodes[y];

		// nodes[y] is nonsense. useless
	}

	bool in_same_tree(int x, int y) {
		return find_root(x) == find_root(y);
	}

	int size(int x) {
		return nodes[find_root(x)];
	}
};

struct Edge {
	int from, to;
	float len;

	// precede "len" when order (use in FUNC kruskal)
	bool operator<(const Edge& o) const {
		return len < o.len;
	}
};

struct Graph {
	vector<Edge> E;

	// calculate sum of len of "Minimum Spanning Tree"
	void kruskal() {
		sort(E.begin(), E.end());

		UnionFind uf(N);
		// float min_len = 0.0;

		for (int i = 0; i < (int)E.size(); i++) {
			Edge& e = E[i];
			if (!uf.in_same_tree(e.from, e.to)) {
				// OK if circle cannot be made even when e is added.
				// cout << e.from << "->" << e.to << "by" << e.len << endl;
				//

				// save in adj_MST for make_pre_trip
				adj_MST[e.from].push_back(e.to);
				adj_MST[e.to].push_back(e.from);
				// min_len += e.len;
				uf.unite_tree(e.from, e.to);
			}
		}
	return;
	}
};

Graph G;

void make_pre_trip() {
	// make trip by follow MST
	int from = 0;
	int to = adj_MST[0].back();
	adj_MST[0].pop_back();

	pre_trip.push_back(from);
	visited_mst[from] = 1;

	while (1) {
		//cout << from << "->" << to << endl;
		pre_trip.push_back(to);
		visited_mst[to] = 1;
		
		// find next place
		from = to;
		
		int size = adj_MST[from].size();
		//cout << size << endl;
		if (size == 0) {
			// end
			break;
		}

		if (size == 1) {
			// go back is ok
			to = adj_MST[from][0];
			adj_MST[from].pop_back();
		}
		else {
			for (int i = size- 1; i >= 0; i--) {
				if (!visited_mst[adj_MST[from][i]]) {
					to = adj_MST[from][i];
					adj_MST[from].erase(adj_MST[from].begin() + i);
					break;
				}
				else {
					continue;
				}
			}
		}
	}

	return;
}


void make_trip() {

	// make trip from pre_trip
	// not add duplication

	for (auto num : pre_trip) {
		if (!visited_sub[num]) {
			trip.push_back(num);
		}
		visited_sub[num] = 1;
	}

}
	
	
void make_distance(vector<P> data) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			float x0 = data[i].first;
			float x1 = data[j].first;
			float y0 = data[i].second;
			float y1 = data[j].second;
			float len  = sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0));

			// array
			dis[i][j] = len;
			
			if (i != N - 1 && i < j){ 
			// vector for order
				Edge e;
				e.from = i;
				e.to = j;
				e.len = len;
				G.E.push_back(e);
			}
		}
	}
}

/*
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
*/

float cal_total_len(vector<int> trip) {

	float len = 0.0;
	for (int i = 0; i < N - 1; i++) {
		len += dis[trip[i]][trip[i+1]];
	}
	len += dis[trip[N - 1]][trip[0]];

	return len;
}

void print_trip(vector<int> trip) {

	for (auto num : trip) {
		cout << num << endl;
	}
}

void print_total_len() {

	cout << "index" << endl;
	float min_len = cal_total_len(trip);
	cout << setprecision(10) << min_len << endl;

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

	G.kruskal();
	make_pre_trip();
	//print_trip(pre_trip);

	make_trip();
	print_trip(trip);

	// print_total_len();
    return 0;
}

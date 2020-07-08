#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream finp("factory.inp");
ofstream fout("factory.out");

typedef struct Lamp {
	
	int num;
	char color;

};

Lamp l[3];
vector<vector<int>> graph;
vector<vector<int>> rgraph;
vector<int> check;
vector<bool> visited;
stack<int> Stack;
int lamp, people;

int rvs(Lamp x) {

	if (x.color == 'B') {
		return x.num + lamp;
	}
	else {
		return x.num;
	}

}

int org(Lamp x) {

	if (x.color == 'B') {
		return x.num;
	}
	else {
		return x.num + lamp;
	}

}

bool isGraph(int x, int y) {

	for (int i = 0; i < graph[x].size(); i++) {
		if (graph[x][i] == y) {
			return true;
		}
	}
	return false;
}

void makeGraph(Lamp x, Lamp y) {

	int rx = rvs(x), ry = rvs(y);
	int ox = org(x), oy = org(y);
	
	if (!isGraph(rx, oy)) {
		graph[rx].push_back(oy);
		graph[ry].push_back(ox);
		rgraph[oy].push_back(rx);
		rgraph[ox].push_back(ry);
	}

}

void dfs(int cur) {

	visited[cur] = true;
	for (int i = 0; i < graph[cur].size(); i++) {
		if (!visited[graph[cur][i]]) dfs(graph[cur][i]);
	}
	Stack.push(cur);

}

void rdfs(int cur, int cnt) {

	visited[cur] = true;
	for (int i = 0; i < rgraph[cur].size(); i++) {
		if (!visited[rgraph[cur][i]]) rdfs(rgraph[cur][i], cnt);
	}

	check[cur] = cnt;

}

int result() {

	for (int i = 1; i < lamp * 2 + 1; i++) {
		if (check[i] == check[i + lamp]) {
			return -1;
		}
	}
	
	return 1;

}

int main(){

	int testcase;
	finp >> testcase;

	while (testcase--) {

		finp >> lamp >> people;
		graph.resize(30005);
		rgraph.resize(30005);

		for (int j = 0; j < people; j++) {
			for (int i = 0; i < 3; i++) {
				finp >> l[i].num >> l[i].color;
			}

			for (int i = 0; i < 3; i++) {
				makeGraph(l[i], l[(i + 1) % 3]);
			}
		}

		visited.resize(30005, false);

		for (int i = 1; i < lamp * 2 + 1; i++) {
			if (!visited[i]) dfs(i);
		}

		visited.clear(); visited.resize(30005, false);
		check.resize(30005);

		int cnt = 1;
		while (!Stack.empty()) {

			int cur = Stack.top();
			Stack.pop();
			if (visited[cur]) continue;

			rdfs(cur, cnt++);
		}

		fout << result() << '\n';
		graph.clear(); rgraph.clear(); visited.clear(); check.clear();

	}

	return 0;
}
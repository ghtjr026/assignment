#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream finp("scc.inp");
ofstream fout("scc.out");

int n, m, result = 0;
vector< vector<int> > graph;
vector< vector<int> > rvs;
vector< bool > visited;
stack<int> Stack;

void dfs(int cur) {

	visited[cur] = true;
	for (int i = 0; i < graph[cur].size(); i++) {

		if (!visited[graph[cur][i]]) dfs(graph[cur][i]);

	}
	Stack.push(cur);

}

void rdfs(int cur) {

	visited[cur] = true;
	for (int i = 0; i < rvs[cur].size(); i++) {
		if (!visited[rvs[cur][i]]) rdfs(rvs[cur][i]);
	}

}

int main() {

	finp >> n >> m;
	graph.resize(n); rvs.resize(n);
	visited.resize(n, false);

	int s, d;
	for (int i = 0; i < m; i++) {
		finp >> s >> d;
		graph[s].push_back(d);
		rvs[d].push_back(s);
	}

	for (int i = 0; i < n; i++) {
		if (!visited[i]) dfs(i);
	}

	visited.clear(); visited.resize(n, false);

	while (!Stack.empty()) {

		int cur = Stack.top();
		Stack.pop();
		if (visited[cur]) {
			continue;
		}

		rdfs(cur);
		result++;
	}

	fout << result;

	return 0;
}
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

ifstream finp("flow.inp");
ofstream fout("flow.out");

typedef struct Points {
	int arrive, weight;
};

vector< vector <Points> > graph;
int parents[10001];

bool isflow(int i, Points& a) {

	if (parents[i] == -1 && a.weight > 0) {
		return true;
	}
	return false;

}

bool solve(int num) {

	memset(parents, -1, sizeof(parents));
	queue<int> dir; dir.push(0);
	parents[0] = 0;
	while (!dir.empty()) {

		int node = dir.front(); dir.pop();
		for (int i = 0; i < graph[node].size(); i++) {

			if (isflow(graph[node][i].arrive, graph[node][i])) {
				dir.push(graph[node][i].arrive);
				parents[graph[node][i].arrive] = node;
				if (graph[node][i].arrive == num - 1) {
					return true;
				}
			}
		}
	}
	return false;

}

int main() {

	int Size;
	finp >> Size;

	graph.resize(Size);

	while (1) {
		int s, a, w;
		finp >> s >> a >> w;
		if (s == -1) {
			break;
		}
		graph[s].push_back({ a,w });
		graph[a].push_back({ s,w });
	}

	int result = 0;
	while (solve(Size)) {
		int cur = Size - 1, MIN = 987654321;
		while (1) {
			int next = parents[cur];
			for (int i = 0; i < graph[cur].size(); i++) {
				if (graph[cur][i].arrive == next) {
					MIN = min(MIN, graph[cur][i].weight);
					break;
				}
			}
			if (next == 0) {
				break;
			}
			cur = next;
		}
		result += MIN;
		cur = Size - 1;
		while (1) {
			int next = parents[cur];
			for (int i = 0; i < graph[cur].size(); i++) {
				if (graph[cur][i].arrive == next) {
					graph[cur][i].weight -= MIN;
					break;
				}
			}
			for (int i = 0; i < graph[next].size(); i++) {
				if (graph[next][i].arrive == cur) {
					graph[next][i].weight -= MIN;
					break;
				}
			}
			if (next == 0) {
				break;
			}
			cur = next;
		}
	}

	fout << result << '\n';

	return 0;
}
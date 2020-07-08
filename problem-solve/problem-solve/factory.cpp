#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

ifstream finp("factory.inp");
ofstream fout("factory.out");

typedef struct checkup {

	int mno, start, day;

}checkup;

int testcase, n, d;
vector<vector<int>> graph;
vector<vector<int>> rgraph;
vector<checkup> machine;
vector<checkup> run;
vector<int> check;
vector<int> visited;
stack<int> Stack;

bool comp(const checkup &a, const checkup &b) {
	return a.start < b.start;
}

int rvs(checkup x) {

	if (x.day == 1) {
		return x.mno + n;
	}
	else {
		return x.mno;
	}

}

int org(checkup x) {

	if (x.day == 1) {
		return x.mno;
	}
	else {
		return x.mno + n;
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

bool isGraph(int x, int y) {

	for (int i = 0; i < graph[x].size(); i++) {
		if (graph[x][i] == y) {
			return true;
		}
	}
	return false;
}

void makeGraph(checkup x, checkup y) {

	int rx = rvs(x), ry = rvs(y);
	int ox = org(x), oy = org(y);

	//if (!isGraph(ox, ry)) {
		graph[rx].push_back(oy);
		graph[ry].push_back(ox);
		rgraph[oy].push_back(rx);
		rgraph[ox].push_back(ry);
	//}

}

bool result() {

	for (int i = 1; i < n+1; i++) {
		if (check[i] == check[i + n]) {
			return false;
		}
	}
	return true;
}

int main() {

	finp >> testcase;
	for (int i = 1; i <= testcase; i++) {
		finp >> n >> d;

		machine.resize((n * 2) + 1);
		graph.resize((n * 2) + 1);
		rgraph.resize((n * 2) + 1);

		int cnt = 1;
		for (int i = 1; i < n * 2 + 1; i++) {
			finp >> machine[i].start;
			machine[i].mno = cnt;
			machine[i].day = i % 2; // day = 1 이면 첫쨋날 0이면 둘쨋날
			if (i % 2 == 0) {
				cnt++;
			}
			run.push_back(machine[i]);
		}

		for (int i = 0; i < n * 2; i += 2) {
			if (run[i].start > run[i + 1].start) {
				int temp = run[i].day;
				run[i].day = run[i + 1].day;
				run[i + 1].day = temp;
			}
		}

		sort(run.begin(), run.end(), comp);

		for (int i = 0; i < run.size() - 1; i++) {

			for (int j = i + 1; j < run.size(); j++) {
				if (run[i].start + d > run[j].start) {
					makeGraph(run[i], run[j]);
				}
				else {
					break;
				}
			}

		}

		visited.resize((n * 2) + 1, false);

		for (int i = 1; i < (n * 2) + 1; i++) {
			if (!visited[i]) dfs(i);
		}

		visited.clear(); visited.resize((n * 2) + 1, false);
		check.resize(n * 2 + 1);

		cnt = 1;
		while (!Stack.empty()) {

			int cur = Stack.top();
			Stack.pop();
			if (visited[cur]) continue;

			rdfs(cur, cnt++);
		}

		fout << "Test Case #" << i << ": ";
		if (result()) {
			fout << "Possible";
		}
		else {
			fout << "Impossible";
		}
		fout << '\n';

		graph.clear(); rgraph.clear(); visited.clear(); check.clear();
		machine.clear(); run.clear();
		
	}

	return 0;
}
#include <fstream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

ifstream finp("mst.inp");
ofstream fout("mst.out");


typedef struct vertax {

	int seq;
	int start;
	int arrive;
	int weight;

}vertax;

int n, m;// n = vertax, m = edge
vertax graph[100001];
int check_seq[100001];

//kruskal
int parent[100001];

//prim
int edgecnt[100001];
int nearest[100001];
int dist[100001];
int supernode[100001];

//kruskal
bool cmp(vertax a, vertax b) {

	if (a.weight == b.weight) return a.seq < b.seq;
	else return a.weight < b.weight;

}

//부모노드 초기화
int get_parent(int a) {
	if (parent[a] == a) {
		return a;
	}
	else {
		return parent[a] = get_parent(parent[a]);
	}
}

//부모노드가 같은지 확인
bool issameparent(int a, int b) {
	return get_parent(a) == get_parent(b);
}

//부모노드의 합병
void Union(int a, int b) {
	a = get_parent(a);
	b = get_parent(b);
	if (a < b) { parent[b] = a; }
	else { parent[a] = b; }
}

//prim
void prim(int str) {

	memset(check_seq, 0, sizeof(check_seq));
	memset(supernode, 0, sizeof(supernode));

	supernode[str] = 1;
	int result = 0;
	int cnt = 0;

	for (int j = 0; j < n - 1; j++) {
		for (int i = 0; i < m; i++) {
			if (supernode[graph[i].start] == 1 && supernode[graph[i].arrive] == 0) {
				supernode[graph[i].arrive] = 1;
				check_seq[cnt] = graph[i].seq;
				result += graph[i].weight;
				cnt++;
				break;
			}
			if (supernode[graph[i].start] == 0 && supernode[graph[i].arrive] == 1) {
				supernode[graph[i].start] = 1;
				check_seq[cnt] = graph[i].seq;
				result += graph[i].weight;
				cnt++;
				break;
			}
		}
	}

	fout << "Tree edges by Prim algorithm with starting vertex " << str << ": " << result << '\n';

	for (int i = 0; i < cnt; i++) {
		fout << check_seq[i] << '\n';
	}

}

int main() {

	//input
	finp >> n >> m;
	for (int i = 0; i < m; i++) {
		graph[i].seq = i;
		parent[i] = i;
		finp >> graph[i].start >> graph[i].arrive >> graph[i].weight;
		edgecnt[graph[i].start]++;
		edgecnt[graph[i].arrive]++;
	}
	//standard : weight
	sort(graph, graph + m, cmp);
	//kruskal algorithm
	int result = 0;
	int cnt = 0;

	for (int i = 0; i < m; i++) {
		if (!issameparent(graph[i].start, graph[i].arrive)) {
			result += graph[i].weight;
			Union(graph[i].start, graph[i].arrive);
			check_seq[cnt] = graph[i].seq;
			cnt++;
		}
	}

	//output
	fout << "Tree edges by Kruskal algorithm: " << result << '\n';
	for (int i = 0; i < cnt; i++) {
		fout << check_seq[i] << '\n';
	}

	//prim algorithm start 0, n/2, n-1

	prim(0);
	prim(n / 2);
	prim(n - 1);

	return 0;
}
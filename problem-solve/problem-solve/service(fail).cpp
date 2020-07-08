/*

	���� �ƴ�

*/


#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
#define MAX 10001
using namespace std;

struct treeNode {
	int edge, capacity;
	treeNode* reverse;
	treeNode(int edge, int capacity) :edge(edge), capacity(capacity), reverse(NULL) {}
};

int n, p, m; // ������, ����Ⱓ ��, �ִ�������
int sink;
int level[MAX], location[MAX];
vector<vector<treeNode*> > network;

bool canFlow(treeNode node) {
	return level[node.edge] == -1 && node.capacity > 0;
}

bool networkFlow() {
	memset(level, -1, sizeof(level));
	queue<int> Queue; Queue.push(0);
	level[0] = 0;
	while (!Queue.empty()) {
		int node = Queue.front(); Queue.pop();
		for (int i = 0; i < network[node].size(); i++) {
			treeNode& next = *network[node][i];
			if (canFlow(next)) {
				level[next.edge] = level[node] + 1;
				Queue.push(next.edge);
			}
		}
	}
	return level[sink] != -1;
}

int renualFlow(int node = 0, int flow = 987654321) {
	if (node == sink) { return flow; }
	for (int i = 0; i < network[node].size(); i++) {
		treeNode& next = *network[node][i];
		if (level[next.edge] == level[node] + 1 && next.capacity > 0) {
			int f = renualFlow(next.edge, min(flow, next.capacity));
			if (f > 0) {
				next.capacity -= f;
				next.reverse->capacity += f;
				return f;
			}
		}
	}
	return 0;
}

void init(ifstream& inp, int& maxFlow) {
	network.clear();
	inp >> n >> p >> m;
	sink = n * p + n;
	for (int i = 1; i <= p; i++) {
		inp >> location[i];
		sink += location[i];
		maxFlow += location[i];
	}
	sink++;
	network.resize(MAX);
	// source -> 1
	for (int i = 1; i <= n; i++) {
		treeNode* a = new treeNode(i, m);
		treeNode* b = new treeNode(0, 0);
		a->reverse = b;
		b->reverse = a;
		network[0].push_back(a);
		network[i].push_back(b);
	}
	// 1 -> 2
	int load = n + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < p; j++) {
			treeNode* a = new treeNode(load, 1);
			treeNode* b = new treeNode(i, 0);
			a->reverse = b;
			b->reverse = a;
			network[i].push_back(a);
			network[load++].push_back(b);
		}
	}
	// 2 -> 3
	for (int i = 1; i <= n; i++) {
		int hopes; inp >> hopes;
		for (int j = 0; j < hopes; j++) {
			int loc, period;
			inp >> loc >> period;
			int u = n + (i - 1) * p + loc,
				v = n * p + n;
			for (int k = 1; k < loc; k++) { v += location[k]; }
			v += period;
			treeNode* a = new treeNode(v, 1);
			treeNode* b = new treeNode(u, 0);
			a->reverse = b;
			b->reverse = a;
			network[u].push_back(a);
			network[v].push_back(b);
		}
	}
	// 3 ->sink
	for (int i = n * p + n + 1; i < sink; i++) {
		treeNode* a = new treeNode(sink, 1);
		treeNode* b = new treeNode(i, 0);
		a->reverse = b;
		b->reverse = a;
		network[i].push_back(a);
		network[sink].push_back(b);
	}
}

int main() {
	ifstream inp("service.inp");
	ofstream out("service.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int result = 0, maxFlow = 0;
		init(inp, maxFlow);
		while (networkFlow()) {
			while (true) {
				int f = renualFlow();
				if (f == 0) { break; }
				result += f;
			}
		}
		out << (result == maxFlow ? 1 : 0) << '\n';
	}
	return 0;
}
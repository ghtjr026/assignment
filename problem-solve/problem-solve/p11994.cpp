#include <fstream>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

ifstream finp("p11994.inp");
ofstream fout("p11994.out");

typedef struct treeNode {
	int parent, color;
};

int n, m, common;
treeNode num;
vector<treeNode> tree;
bool visited[50001];

bool find_ancestor(int x, int y) {

	if (y == 0) {
		return false;
	}
	else if (x == y) {
		return true;
	}
	return find_ancestor(x, tree[y].parent);

}

void find_common(int node) {

	if (visited[node] == true) {
		common = node;
		return;
	}
	visited[node] = true;
	if (tree[node].parent == 0) {
		return;
	}
	return find_common(tree[node].parent);

}

void paint_tree(int node, int c) {

	if (node != common) {
		tree[node].color = c;
	}
	else {
		return;
	}
	return paint_tree(tree[node].parent, c);

}

void solve(int type, int x, int y, int c) {

	common = 0;
	memset(visited, false, sizeof(visited));
	find_common(x);
	find_common(y);

	if (type == 1) { // Change x's father to y
		if (!find_ancestor(x, y)) {
			tree[x].parent = y;
			tree[x].color = c;
			return;
		}
	}
	else if (type == 2) { // Paint all the edges along the path x-y with color c
		if (common) {
			paint_tree(x, c);
			paint_tree(y, c);
		}
		return;
	}
	else { // Count the number of edges along the path x-y, and the total number of colors among these edges
		set<int> color;
		int edge = 0;
		if (common) {
			for (int i = x;; i = tree[i].parent) {
				if (i == common) break;
				color.insert(tree[i].color);
				edge++;
			}
			for (int i = y;; i = tree[i].parent) {
				if (i == common) break;
				color.insert(tree[i].color);
				edge++;
			}
		}
		fout << edge << ' ' << color.size() << '\n';
		return;
	}

}

int main() {

	finp >> n >> m;
	num.parent = 0;
	tree.push_back(num);
	for (int i = 1; i <= n; i++) { // parent
		finp >> num.parent;
		tree.push_back(num);
	}
	for (int i = 1; i <= n; i++) { // color
		finp >> num.color;
		tree[i].color = num.color;
	}


	while (m--) {

		int type, x, y, c = 0;
		finp >> type >> x >> y;
		if (type != 3) {
			finp >> c;
		}
		solve(type, x, y, c);

	}

	return 0;
}
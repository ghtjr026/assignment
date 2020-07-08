#include <fstream>
#include <vector>
#include <algorithm>
#define INF -987654321
using namespace std;

ifstream finp("path.inp");
ofstream fout("path.out");

typedef struct treeNode {

	int weight, left, right;

}Node;

vector<treeNode> tree;
vector<int> preorder;
int result;

void makeTree(int root, int begin, int end) {
	if (begin <= end) {
		int leftsize = preorder[root] - begin;
		int rightsize = end - preorder[root];

		if (leftsize > 0) {
			tree[preorder[root]].left = preorder[root + 1];
			makeTree(root + 1, begin, preorder[root] - 1);
		}
		if (rightsize > 0) {
			tree[preorder[root]].right = preorder[root + leftsize + 1];
			makeTree(root + leftsize + 1, preorder[root] + 1, end);
		}
	}
}

int sumPath(int root) {

	if (root == -1) {
		return INF;
	}

	if (tree[root].left == -1 && tree[root].right == -1) {
		result = max(result, tree[root].weight);
		return tree[root].weight;
	}

	int leftsum = sumPath(tree[root].left);
	int rightsum = sumPath(tree[root].right);

	if (tree[root].left != -1 && tree[root].right != -1) {
		result = max(result, leftsum + rightsum + tree[root].weight);
	}

	return max(leftsum, rightsum) + tree[root].weight;

}

int main() {

	int testcase;
	finp >> testcase;
	while (testcase--) {

		int num;
		finp >> num;
		tree.resize(num);
		preorder.resize(num);
		for (int i = 0; i < num; i++) {
			finp >> tree[i].weight;
			tree[i].left = -1; tree[i].right = -1;
		}
		for (int i = 0; i < num; i++) {
			finp >> preorder[i];
		}
		
		makeTree(0, 0, num - 1);
		result = INF;
		sumPath(preorder[0]);
		fout << result << '\n';

		tree.clear();
		preorder.clear();

	}


	return 0;
}
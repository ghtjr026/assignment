#include <fstream>
#include <stack>
#include <vector>
using namespace std;

ifstream finp("transform.inp");
ofstream fout("transform.out");

int testcase, nodeNum, type;
vector<int> Tree;

int node;
void numToBlock( int fornt, int rear) {

	for (int i = fornt; i < rear; i++) {
		if (Tree[i] == node) {
			node++;
			fout << '(';
			numToBlock(fornt, i);
			fout << ')';
			numToBlock(i + 1, rear);
		}
	}

}

void blockToNum() {
	
	stack<int> Stack;

	int cnt = 0;

	for (int i = 0; i < nodeNum * 2; i++) {
		char b;
		finp >> b;
		if (b == '(') {
			Stack.push(++cnt);
		}
		else {
			fout << Stack.top() << ' ';
			Stack.pop();
		}
	}

}

int main() {

	finp >> testcase;
	while (testcase--) {

		finp >> nodeNum >> type;
		fout << nodeNum << ' ';
		switch (type) {
		case 0:
			Tree.clear(); node = 1;
			for (int i = 0; i < nodeNum; i++) {
				int num;
				finp >> num;
				Tree.push_back(num);
			}
			numToBlock(0, nodeNum);
			break;
		case 1:
			blockToNum();
			break;
		}
		fout << '\n';
	}

	return 0;
}
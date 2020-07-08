#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

int main() {

	ifstream finp("tree.inp");
	ofstream fout("tree.out");

	vector<string> read;

	int testcase;
	int R_cnt = 0;

	finp >> testcase;
	while (testcase--) {
		stack<string> Stack;
		string temp;
		finp >> temp;
		read.push_back(temp);
		Stack.push(temp);
		while (!Stack.empty()) {
			finp >> temp;
			read.push_back(temp);
			if (temp == ")") {
				Stack.pop();
			}
			else if(temp == "("){
				Stack.push(temp);
			}
		}
		for (int i = 0; i < read.size(); i++) {
			fout << read[i] << ' ';
		}
		
		fout << '\n' << "Preorder" << '\n';

		for (int i = 0; i < read.size(); i++) {
			if (read[i] == "(") {
				fout << 'r' << R_cnt << '\n';
				R_cnt++;
			}
			else if(read[i] != ")") {
				fout << read[i] << '\n';
			}
		}

		fout << "Inorder" << '\n';
		stack<int> S;
		R_cnt = 0;

		for (int i = 0;i < read.size(); i++) {

			if (read[i] == "(") {
				S.push(R_cnt);
				R_cnt++;
			}
			else if (read[i] != ")") {
				fout << read[i] << '\n';
				if (!S.empty()) {
					fout << 'r' << S.top() << '\n';
					S.pop();
				}
			}

		}
		R_cnt = 0;

		read.clear();
	}
	
	

	return 0;
}
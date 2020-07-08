#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

ifstream finp("p10150.inp");
ofstream fout("p10150.out");

typedef struct Words {
	string w;
	bool ch;
	vector<int> Graph;
	int parents;
}Words;

typedef struct result {
	int idx;
	string w;
}result;

deque<result> BFSq;
Words words[26000];

bool isdubblet(string a, string b) {

	if (a.length() != b.length()) {
		return false;
	}
	int cnt = 0;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] != b[i]) {
			cnt++;
		}
		if (cnt > 1) {
			return false;
		}
	}
	return true;

}

void isGraph(int num) {

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (isdubblet(words[i].w, words[j].w) && words[i].w != words[j].w) {
				words[i].Graph.push_back(j);
			}
		}
	}

}

bool BFS(string fin, int num) {
	while (1) {

		if (!BFSq.empty()) {
			int index = BFSq.front().idx;
			for (int i = 0; i < num; i++) {
				if (!words[i].ch) {
					if (isdubblet(words[index].w, words[i].w)) {
						result s;
						s.idx = i;
						s.w = words[i].w;
						BFSq.push_back(s);
						words[i].ch = true;
						words[i].parents = index;
						if (words[i].w == fin) return true;
					}
				}
			}
			BFSq.pop_front();
		}
		else {
			return false;
		}

	}

}

void print(int s, int f) {

	if (f != s) {
		print(s, words[f].parents);
	}
	fout << words[f].w << '\n';

}

int main() {

	int num;
	for (num = 0;;num++) {

		char read[19];
		finp.getline(read, 20);
		words[num].w = read;
		if (words[num].w.empty()) break;
		if (words[num].w.back() != ' ') {
			words[num].w.push_back(' ');
		}

	}
	
	//isGraph(num);

	string sta, fin;
	while (finp >> sta >> fin) {
		if (sta.empty()) {
			break;
		}
		sta.push_back(' ');
		fin.push_back(' ');

		result s;
		s.w = sta;
		for (int start = 0;; start++) {
			if (words[start].w == s.w) {
				s.idx = start;
				words[start].ch = true;
				break;
			}
		}

		BFSq.push_back(s);
		bool l = BFS(fin, num);

		if (sta.length() != fin.length() || !l) {
			fout << "No solution." << '\n';
		}
		else {
			result f;
			f.w = fin;
			for (int final = 0;; final++) {
				if (words[final].w == f.w) {
					f.idx = final;
					break;
				}
			}

			print(s.idx, f.idx);
		}

		BFSq.clear();
		for (int i = 0; i < 26000; i++) {
			words[i].ch = false;
			words[i].parents = 0;
		}
		fout << '\n';

	}

	return 0;
}

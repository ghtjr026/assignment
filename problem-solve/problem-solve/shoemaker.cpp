#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream finp("shoemaker.inp");
ofstream fout("shoemaker.out");

typedef struct work {

	int seq, day, penalty;

};

int testcase, num;
vector<work> Work;

void solve() {

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num - 1; j++) {
			if (Work[j].day * Work[j + 1].penalty > Work[j + 1].day* Work[j].penalty) {
				swap(Work[j], Work[j + 1]);
			}
		}
	}

}

int main() {

	finp >> testcase;
	while (testcase--) {

		finp >> num;
		Work.resize(num);

		for (int i = 0; i < num; i++) {
			finp >> Work[i].day >> Work[i].penalty;
			Work[i].seq = i + 1;
		}

		solve();
		for (int i = 0; i < num; i++) {
			fout << Work[i].seq << ' ';
		}
		fout << "\n";

	}

	return 0;
}
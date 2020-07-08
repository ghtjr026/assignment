#include <fstream>
#include <set>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

ifstream finp("rectangle2.inp");
ofstream fout("rectangle2.out");

typedef struct Pair {
	int i, j;
}Pair;

vector<int> dp;
set<double> cnt;
int testcase;

void solve() {

	for (int i = 2; i < 500; i++) {

		for (int j = 1; j < i; j++) {

			int Size = cnt.size();

			int a = 2 * i * j, b = i * i - j * j;
			if (a > b) swap(a, b);
			cnt.insert((double)b / a);
			if (Size != cnt.size()) {
				dp.push_back(2 * (a + b));
			}

		}

	}

}

int getResult(int L) {

	int result = 0;
	for (auto i = dp.begin(); i != dp.end(); i++) {
		L -= *i;
		result++;
		if (L <= 0) {
			break;
		}
	}

	if (L < 0) {
		return --result;
	}

	return result;
}

int main() {

	finp >> testcase;
	solve();
	sort(dp.begin(), dp.end());
	while (testcase--) {

		int L;
		finp >> L;
		fout << getResult(L) << '\n';

	}

	return 0;
}

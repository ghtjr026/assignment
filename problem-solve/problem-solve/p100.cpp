#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

ifstream finp("p100.inp");
ofstream fout("p100.out");

long long arr[1000001];

void solve(int num, long long result, int cnt) {

	cnt++;

	if (result % 2 == 1) {
		result = result * 3 + 1;
		if (result < num) {
			arr[num] = arr[result] + cnt;
			return;		
		}
		solve(num, result, cnt);
	}
	else {
		result = result / 2;
		if (result < num) {
			arr[num] = arr[result] + cnt;
			return;
		}
		solve(num, result, cnt);
	}

}

int main() {

	arr[1] = 1;
	for (int i = 2; i < 1000001; i++) {
		solve(i, i, 0);
	}

	int fi, se;
	while (finp >> fi >> se) {
		long long result = 0;
		fout << fi << ' ' << se << ' ';

		if (fi > se) {
			int temp = fi;
			fi = se;
			se = temp;
		}

		for (int i = fi; i <= se; i++) {
			result = max(result, arr[i]);
		}

		fout << result << '\n';
	}

	return 0;
}
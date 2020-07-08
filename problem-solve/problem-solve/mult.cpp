#include <fstream>
#include <cmath>
using namespace std;

ifstream finp("mult.inp");
ofstream fout("mult.out");

int testcase, num, result;

void solve(int div, int Num) {

	bool flag = true;
	for (int i = 2; i < Num; i++) {
		if (Num % i == 0) {
			flag = false;
			break;
		}
	}
	if (!flag) {
		for (int i = div; i <= sqrt(Num); i++) {

			if (Num % i == 0) {
				result++;
				solve(i, Num / i);
			}

		}
	}

}

int main() {

	finp >> testcase;
	while (testcase--) {

		finp >> num;
		result = 0;

		solve(2, num);
		fout << num << ' ' << result << '\n';

	}

	return 0;
}
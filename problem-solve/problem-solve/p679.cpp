#include <fstream>
#include <cstring>
using namespace std;

ifstream finp("p679.inp");
ofstream fout("p679.out");

bool arr[1048577];

int solve(int d, int b) {

	int i;

	for (int ball = 0; ball < b; ball++) {
		
		i = 1;

		for (int depth = 1; depth < d; depth++) {

			if (arr[i] == false) {
				arr[i] = true;
				i = i * 2;
			}
			else if (arr[i] == true) {
				arr[i] = false;
				i = i * 2 + 1;
			}

		}

	}

	return i;
}

int main() {

	int testcase;
	finp >> testcase;

	while (testcase--) {
		
		memset(arr, false, sizeof(arr));

		int d, b;
		finp >> d >> b;
		int result = solve(d, b);

		fout << result << '\n';

	}

	return 0;
}
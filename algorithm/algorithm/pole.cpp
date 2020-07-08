#include <fstream>
using namespace std;

ifstream finp("pole.inp");
ofstream fout("pole.out");

long long int Case[21][21][21];
int L, l, r;

long long int soltion() {
	
	if (L == 1) {
		if (L == 1 && r == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
	
		if (l + r >= L + 2) {
			return 0;
		}

		for (int i = 1; i < L; i++) {
			Case[i][i][1] = 1;
			Case[i][1][i] = 1;
		}

		for (int i = 2; i < L + 1; i++) {
			for (int j = 1; j < l + 1; j++) {
				for (int k = 1; k < r + 1; k++) {
					Case[i][j][k] = (Case[i - 1][j][k] * (i - 2)) + Case[i - 1][j - 1][k] + Case[i - 1][j][k - 1];
				}
			}
		}

	}
	return Case[L][l][r];

}

int main() {

	int testcase;
	finp >> testcase;

	while (testcase--) {

		finp >> L >> l >> r;
		long long int result = soltion();
		fout << result << '\n';

	}

	finp.close(); fout.close();
	return 0;
}
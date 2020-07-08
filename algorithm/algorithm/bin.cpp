#include <fstream>
#include <cstring>
#include <algorithm>
#define INF 9999999
using namespace std;

ifstream finp("bin.inp");
ofstream fout("bin.out");

int n, m;
int home[501];
int basic_bin[501][501];
int mul_bin[501][501];

void set_basic_bin() {
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			basic_bin[i][j] = basic_bin[i][j - 1] + home[j] - home[i + (j - i) / 2];
		}
	}
}

int main() {
	int testcase;
	finp >> testcase;
	while (testcase--) {
		finp >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				mul_bin[i][j] = INF;
			}
		}
		memset(basic_bin, 0, sizeof(basic_bin));
		for (int i = 1; i <= n; i++) {
			finp >> home[i];
		}
		sort(home, home + n + 1);
		set_basic_bin();
		for (int i = 1; i <= n; i++) { // Áý
			for (int j = 1; j <= m; j++) { // Åë
				for (int k = 1; k <= i; k++) {
					mul_bin[i][j] = min(mul_bin[i][j], mul_bin[k - 1][j - 1] + basic_bin[k][i]);
				}
			}
		}
		fout << mul_bin[n][m] << '\n';
	}
	finp.close();
	fout.close();
	return 0;
}
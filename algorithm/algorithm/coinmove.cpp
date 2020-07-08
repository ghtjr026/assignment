#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream finp("coinmove.inp");
ofstream fout("coinmove.out");

bool game[1000001][10];
int p, k, s;

int solution(int position, int moved) {

	if (position < 0) return false;
	if (position != 0 && position % p == 0) return false;
	else {
		for (int i = 1; i <= k; i++) {
			if (i != moved && game[position][i] == true) {
				return false;
			}
		}
		return true;
	}

}

int main() {

	int testcase;
	finp >> testcase;

	while (testcase--) {

		finp >> p >> k >> s;

		for (int i = 1; i <= s; i++) {
			for (int j = 1; j <= k; j++) {
				game[i][j] = solution(i - j, j);
			}
		}

		bool check = false;
		for (int i = 1; i <= k; i++) {
			if (game[s][i] == true) {
				fout << s - i << '\n';
				check = true;
				break;
			}
		}
		if (check == false) fout << "-1\n";
		memset(game, false, sizeof(game));

	}

	finp.close();
	fout.close();

	return 0;
}
#include <fstream>
#include <algorithm>
using namespace std;

ifstream finp("coin.inp");
ofstream fout("coin.out");

int game[7][7][7];

void set_game() {

	game[3][3][3] = 1;

	for (int i = 3; i < 7; i++) {
		for (int j = 3; j < 7; j++) {
			for (int k = 3; k < 7; k++) {
				if(i == 3 && j == 3 && k ==3) continue;
				else {
					if (game[i - 1][j][k] == -1 || game[i][j - 1][k] == -1 || game[i][j][k - 1] == -1) {
						game[i][j][k] = 1;
					}
					else if (game[i - 2][j][k] == -1 || game[i][j - 2][k] == -1 || game[i][j][k - 2] == -1) {
						game[i][j][k] = 1;
					}
					else if (game[i - 3][j][k] == -1 || game[i][j - 3][k] == -1 || game[i][j][k - 3] == -1) {
						game[i][j][k] = 1;
					}
					else {
						game[i][j][k] = -1;
					}
				}
			}
		}
	}

}

int main() {

	int testcase;
	finp >> testcase;

	set_game();

	while (testcase--) {

		int a, b, c;
		finp >> a >> b >> c;

		fout << '(' << a << ' ' << b << ' ' << c << ") : " << game[a % 4 + 3][b % 4 + 3][c % 4 + 3] << '\n';

	}

	finp.close(); fout.close();
	return 0;
}
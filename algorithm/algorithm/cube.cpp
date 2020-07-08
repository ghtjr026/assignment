#include <fstream>
#include <algorithm>
using namespace std;

ifstream finp("cube.inp");
ofstream fout("cube.out");
int game[201][201][201];

void solution() {
	for (int i = 1; i < 201; i++) {
		for (int j = i; j < 201; j++) {
			for (int k = j; k < 201; k++) {
				if(game[i][j][k] == 99999999){
					for (int w = 1; w < i / 2 + 1; w++) {
						game[i][j][k] = min(game[i][j][k], game[w][j][k] + game[i - w][j][k]);
					}
					for (int h = 1; h < j / 2 + 1; h++) {
						game[i][j][k] = min(game[i][j][k], game[i][h][k] + game[i][j - h][k]);
					}
					for (int l = 1; l < k / 2 + 1; l++) {
						game[i][j][k] = min(game[i][j][k], game[i][j][l] + game[i][j][k - l]);
					}
					game[j][i][k] = game[j][k][i] = game[k][j][i] = game[i][k][j] = game[k][i][j] = game[i][j][k];
				}
			}
		}
	}
}

int main() {
	int testcase;
	finp >> testcase;
	for (int i = 1; i < 201; i++) {
		for (int j = 1; j < 201; j++) {
			for (int k = 1; k < 201; k++) {
				if (i == j && j == k && i == k) {
					game[i][j][k] = 1;
				}
				else {
					game[i][j][k] = 99999999;
				}
			}
		}
	}
	solution();
	while (testcase--) {
		int weight, hieght, Long;
		finp >> weight >> Long >> hieght;
		fout << game[weight][Long][hieght] << '\n';
	}
	return 0;
}
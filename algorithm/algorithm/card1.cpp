#include <fstream>
#include <vector>
#define MIN -93939
using namespace std;

ifstream finp("card.inp");
ofstream fout("card.out");

int dx[3] = { 2,3,4 };
int card[1000];
int bigest[3][1000];

void set_bigest(int Size) {
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			bigest[i][j] = card[j];
		}
	}

	for (int i = 0; i < 3; i++) {
		bigest[i][Size - 2] = MIN;
	}

}

int MAX(int a, int b, int c) {

	if (a > b) {
		if (a > c) {
			return a;
		}
		else {
			return c;
		}
	}
	else {
		if (b > c) {
			return b;
		}
		else {
			return c;
		}
	}

}

int Max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

void Solution(int Size) {

	for (int i = 3; i < Size - 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (i - dx[j] < 0) {
				bigest[j][i] = MIN;
			}
			else {
				if (j == 0) {
					bigest[j][i] = Max(bigest[1][i - dx[j]], bigest[2][i - dx[j]]) + card[i];
				}
				else {
					bigest[j][i] = MAX(bigest[0][i - dx[j]], bigest[1][i - dx[j]], bigest[2][i - dx[j]]) + card[i];
				}
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (Size - 1 - dx[i] < 0) {
			bigest[i][Size - 1] = MIN;
		}
		else {
			if (i == 0) {
				bigest[i][Size - 1] = Max(bigest[1][Size - 1 - dx[i]], bigest[2][Size - 1 - dx[i]]) + card[Size - 1];
			}
			else {
				bigest[i][Size - 1] = MAX(bigest[0][Size - 1 - dx[i]], bigest[1][Size - 1 - dx[i]], bigest[2][Size - 1 - dx[i]]) + card[Size - 1];
			}
		}
	}

}

int main() {

	int testcase;
	finp >> testcase;

	while (testcase--) {

		int num, read;
		finp >> num;

		for (int i = 0; i < num; i++) {
			finp >> read;
			card[i] = read;
		}

		set_bigest(num);
		Solution(num);

		int result = MIN;

		for (int i = 0; i < 3; i++) {
			if (result < bigest[i][num - 1]) {
				result = bigest[i][num - 1];
			}
		}

		fout << result << '\n';

	}

	return 0;
}
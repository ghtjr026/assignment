#include <fstream>
using namespace std;

ifstream finp("card.inp");
ofstream fout("card.out");

int alice[10000][10000], computer[10000][10000];

int minimum(int a, int b) {

	if (a > b) {
		return b;
	}
	else {
		return a;
	}

}

void solution(int num) {

	for (int j = 1; j < num; j++) {
		for (int i = 0; i + j < num; i++) {
			computer[i][i + j] = minimum(alice[i][i + j - 1], alice[i + 1][i + j]);
			alice[i][i + j] = alice[i][i + j - 1] + alice[i + j][i + j] + computer[i][i + j - 1] - computer[i][i + j];
		}
	}

}

int main() {

	int testcase;
	finp >> testcase;

	while (testcase--) {

		int num, card;
		finp >> num;

		for (int i = 0; i < num; i++) {
			finp >> card;
			alice[i][i] = card;
		}

		solution(num);
		fout << alice[0][num - 1] << '\n';

	}

	finp.close(); fout.close();
	return 0;
}
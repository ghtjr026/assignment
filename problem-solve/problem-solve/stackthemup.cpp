#include <fstream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

FILE* finp = fopen("stackthemup.inp", "rt");
ofstream fout("stackthemup.out");

int shuffle[101][53], card[53];
string suits[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };
string values[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

int main() {

	int testcase;
	fscanf(finp, "%d\n", &testcase);
	for (int t = 0; t < testcase; t++) {
		int n;
		fscanf(finp, "%d\n", &n);
		for (int i = 1; i < n + 1; i++) {
			for (int j = 1; j < 53; j++) {
				fscanf(finp, "%d", &shuffle[i][j]);
			}
		}
		for (int i = 1; i < 53; i++) {
			card[i] = i;
		}

		char line[101];
		fgets(line, 101, finp);
		while (fgets(line, 101, finp)) {
			if (line[0] == '\n') break;
			int num, deck[53];
			sscanf(line, "%d", &num);

			for (int i = 1; i < 53; i++) {
				deck[i] = card[shuffle[num][i]];
			}
			for (int i = 1; i < 53; i++) {
				card[i] = deck[i];
			}
		}
		if (t > 0) {
			fout << '\n';
		}
		for (int i = 1; i < 53; i++) {
			fout << values[(card[i] - 1) % 13] << " of " << suits[(card[i] - 1) / 13] << '\n';
		}

	}

	return 0;
}
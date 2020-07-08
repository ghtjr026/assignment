#include <fstream>
#include <string.h>
using namespace std;

int main() {

	ifstream finp("bowling.inp");
	ofstream fout("bowling.out");

	int testcase;
	int frame[10][3];

	finp >> testcase;

	for (int i = 0; i < testcase; i++) {

		memset(frame, 0, sizeof(frame));

		for (int j = 0; j < 10; j++) { // ют╥б

			finp >> frame[j][0];

			if (j == 9) {
				finp >> frame[j][1];
				if (frame[j][0] + frame[j][1] >= 10) {
					finp >> frame[j][2];
				}
				break;
			}

			if (frame[j][0] != 10) {
				finp >> frame[j][1];
			}

		}

		int total = 0;

		for (int j = 0; j < 8; j++) {

			total += frame[j][0] + frame[j][1];

			if (frame[j][0] == 10) { // strike
				if (frame[j + 1][0] == 10) {
					total += frame[j + 1][0] + frame[j + 2][0];
				}
				else {
					total += frame[j + 1][0] + frame[j + 1][1];
				}
			}
			else if (frame[j][0] + frame[j][1] == 10) { //spare
				total += frame[j + 1][0];
			}
		}

		//9frame
		total += frame[8][0] + frame[8][1];

		if (frame[8][0] == 10) {
			total += frame[9][0] + frame[9][1];
		}
		else if (frame[8][0] + frame[8][1] == 10) {
			total += frame[9][0];
		}

		//10frame
		total += frame[9][0] + frame[9][1] + frame[9][2];

		fout << total << endl;

	}

	return 0;
}
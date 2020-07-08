#include <fstream>
#include <algorithm>
#include <stdio.h>
#pragma warning (disable : 4996)
using namespace std;

ifstream finp("p10137.inp");
FILE* fout = fopen("p10137.out", "w");

int student[1001];

int main() {

	int testcase;
	while (1) {

		finp >> testcase;
		if (testcase == 0) break;

		int dallor, cent, sum = 0;
		char dot;

		for (int i = 0; i < testcase; i++) {
			finp >> dallor >> dot >> cent;
			student[i] = dallor * 100 + cent;
			sum += student[i];
		}

		int avr = (int)(((double)sum / testcase) + 0.51);
		int lowresult = 0, upresult = 0;

		for (int i = 0; i < testcase; i++) {
			if (student[i] < avr) {
				lowresult += (avr - student[i]);
			}
			if (student[i] > avr) {
				upresult += (student[i] - avr);
			}
		}

		int result = min(lowresult, upresult);

		fprintf(fout, "$%d.%02d\n", result / 100, result % 100);

	}

	return 0;
}

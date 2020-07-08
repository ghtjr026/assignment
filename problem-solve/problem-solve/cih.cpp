#include <fstream>
#include <cmath>
using namespace std;

ifstream finp("cih.inp");
ofstream fout("cih.out");

unsigned long long height, worker;
unsigned long long mul, mulpuls1;
int p;

void findPow() {

	bool flag = false;
	mul = 1;
	while (1) {
		unsigned long long x = 1, xpuls1 = 1;

		for (int i = 0;; i++) {
			if (x == worker && xpuls1 == height) {
				flag = true;
				p = i;
				break;
			}
			if (x > worker || xpuls1 > height) break;
			if (x == 0 || xpuls1 == 0) break;

			x *= mul;
			xpuls1 *= mul + 1;
		}
		if (flag){
			mulpuls1 = mul + 1;
			break;
		}
		mul++;
	}

}

unsigned long long getNonWorker() {

	int sum = 1;
	unsigned long long result = 1;
	for (int i = 1; i < p; i++) {
		sum *= mul;
		result += sum;
	}
	return result;
}

unsigned long long getHeight() {

	int num = 1;
	int h = height;
	unsigned long long result = height;
	for (int i = 0; i < p; i++) {
		num *= mul;
		h /= mulpuls1;
		result += num * h;
	}
	return result;

}

int main() {

	while (finp >> height >> worker) {
		if (height == 0 && worker == 0) break;

		if (height == 1 && worker == 1) fout << "0 1\n";
		else {

			findPow();
			long long nonWorkerCat = getNonWorker();
			long long totalHeight = getHeight();

			fout << nonWorkerCat << ' ' << totalHeight << '\n';

		}
	}

	return 0;
}
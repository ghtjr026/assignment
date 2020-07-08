#include <fstream>
using namespace std;

ifstream finp("ones.inp");
ofstream fout("ones.out");

int num;

void divide() {

	int i;
	int mod = 1;
	for (i = 1;; i++) {
		mod = mod % num;
		if (mod == 0) break;
		mod = (mod % num) * (10 % num) + 1;
	}
	fout << i << '\n';

}

int main() {

	while (finp >> num) {
		divide();
	}

	return 0;
}
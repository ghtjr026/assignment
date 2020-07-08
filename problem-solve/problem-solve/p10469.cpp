#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream finp("p10469.inp");
ofstream fout("p10469.out");

unsigned long long int solve(unsigned long long int num, unsigned long long int num1) {

	vector<unsigned long long int> a;
	vector<unsigned long long int> b;
	for (long i = 1; num > 0; i *= 10) {
		int binary = num % 2;
		a.push_back(binary);
		num /= 2;
	}
	for (long i = 1; num1 > 0; i *= 10) {
		int binary = num1 % 2;
		b.push_back(binary);
		num1 /= 2;
	}

	vector<unsigned long long int> r;
	int size = min(a.size(), b.size());
	int s;

	
	for (s = 0; s < size; s++) {
		r.push_back(a[s] + b[s]);
		if (r[s] > 1) {
			r[s] = 0;
		}
	}

	if (a.size() == size) {
		for (; s < b.size(); s++) {
			r.push_back(b[s]);
		}
	}
	else {
		for (; s < a.size(); s++) {
			r.push_back(a[s]);
		}
	}

	unsigned long long int ten = r[0];
	unsigned long long int mul = 2;
	for (int i = 1; i < r.size(); i++, mul *= 2) {
		ten += r[i] * mul;
	}

	return ten;
}


int main() {

	unsigned long long int a, b;
	while (1) {

		finp >> a >> b;
		if (finp.eof()) {
			break;
		}
		
		unsigned long long int result = solve(a, b);

		fout << result << '\n';

	}
	
	return 0;
}
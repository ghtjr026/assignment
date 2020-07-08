#include <fstream>
#include <cmath>
using namespace std;

ifstream finp("popg.inp");
ofstream fout("popg.out");

int main() {

	double n, num;
	while (finp >> n >> num) {
		fout << pow(num,1/n) <<'\n';
	}

	return 0;
}
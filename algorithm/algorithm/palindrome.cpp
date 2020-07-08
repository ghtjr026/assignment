#include <string.h>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int LCS[1000][1000];

void repeat(string arr, string rra) {

	for (int i = 1; i < rra.size(); i++) {

		for (int j = 1; j < arr.size(); j++) {

			if (rra[i] == arr[j]) {
				
				LCS[i][j] = LCS[i - 1][j - 1] + 1;

			}
			else {
				if (LCS[i][j-1] >= LCS[i-1][j]) {
					LCS[i][j] = LCS[i][j - 1];
				}
				else {
					LCS[i][j] = LCS[i - 1][j];
				}
			}

		}

	}

}

int main() {

	ifstream finp("palindrome.inp");
	ofstream fout("palindrome.out");

	int testcase, num;
	string arr, rra;

	finp >> testcase;

	for (int i = 0; i < testcase; i++) {

		memset(LCS, 0, sizeof(LCS));

		finp >> arr;
		rra = arr;
		reverse(rra.begin(), rra.end());
		rra = '0' + rra;
		arr = '0' + arr;

		repeat(arr, rra);
		num = arr.size() - 1 - LCS[arr.size() - 1][rra.size() - 1];

		if(num<3){
			fout << num << endl;
		}
		else {
			fout << -1 << endl;
		}

	}

	return 0;
}
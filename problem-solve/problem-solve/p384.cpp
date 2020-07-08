#include <string>
#include <fstream>
using namespace std;

ifstream finp("p384.inp");
ofstream fout("p384.out");

bool check_slump(string sub) {

	if ((sub[0] == 'D' || sub[0] == 'E') && sub[1] == 'F') {
		int idx;
		for (idx = 2; ; idx++) {
			if (sub[idx] != 'F') {
				break;
			}
		}
		if (sub[idx] == 'D' || sub[idx] == 'E') {
			return check_slump(sub.substr(idx, sub.length() - idx));
		}
		else if (sub[idx] == 'G' && idx == sub.length() - 1) { // must last 'G'
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

bool check_slimp(string sub) {

	if (sub[0] != 'A') return false;
	if (sub.length() == 2 && sub[1] == 'H') return true;
	if (sub[sub.length() - 1] != 'C') return false;
	if (sub[1] == 'B') {
		return check_slimp(sub.substr(2, sub.length() - 3)); // A + B + slimp + C
	}
	else {
		return check_slump(sub.substr(1, sub.length() - 2)); // A + slump + C
	}

}

int main() {

	int testcase;
	finp >> testcase;
	fout << "SLURPYS OUTPUT" << '\n';
	while (testcase--) {

		string word;
		finp >> word;

		bool result = false;
		for (int i = word.length() - 1; i > -1; i--) {
			if (word[i] == 'C' || word[i] == 'H') {
				result = check_slimp(word.substr(0, i + 1));
				if (result) {
					result = check_slump(word.substr(i + 1, word.length() - i - 1));
				}
				break;
			}
		}

		if (result) {
			fout << "YES";
		}
		else {
			fout << "NO";
		}
		fout << '\n';

	}
	fout << "END OF OUTPUT" << '\n';

	return 0;
}
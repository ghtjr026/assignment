#include <fstream>
#include <string>
#include <vector>
using namespace std;

ifstream finp("pandora.inp");
ofstream fout("pandora.out");
bool y, x;
int result, vec;
string num;
vector<int> str;

// 0 : down 1 : left 2 : up 3 : right
//1 0 3, 3 2 1 yÃà
//2 1 0, 0 3 2 xÃà

int main() {

	int testcase;
	finp >> testcase;

	while (testcase--) {

		finp >> num;

		result = 2;
		y = false, x = false;

		if (num[0] == 'L') str.push_back(0);
		else str.push_back(2);

		//change index
		for (int i = 1; i < num.size(); i++) {
			
			if (str[i - 1] == 0) {
				if (num[i] == 'L') {
					str.push_back(1);
				}
				else {
					str.push_back(3);
				}
			}
			else if (str[i - 1] == 1) {
				if (num[i] == 'L') {
					str.push_back(2);
				}
				else {
					str.push_back(0);
				}
			}
			else if (str[i - 1] == 2) {
				if (num[i] == 'L') {
					str.push_back(3);
				}
				else {
					str.push_back(1);
				}
			}
			else if (str[i - 1] == 3) {
				if (num[i] == 'L') {
					str.push_back(0);
				}
				else {
					str.push_back(2);
				}
			}

		}

		str.push_back(str[0]);
		str.push_back(str[1]);

		for (int i = 0; i < num.size(); i++) {
			if (str[i] == 1 && str[i + 1] == 0 && str[i + 2] == 3) {
				y = true;
			}
			else if (str[i] == 3 && str[i + 1] == 2 && str[i + 2] == 1) {
				y = true;
			}
			else if (str[i] == 2 && str[i + 1] == 1 && str[i + 2] == 0) {
				x = true;
			}
			else if (str[i] == 0 && str[i + 1] == 3 && str[i + 2] == 2) {
				x = true;
			}
		}

		if (y == true) {
			result--;
		}
		if (x == true) {
			result--;
		}

		fout << result << '\n';

		str.clear();

	}

	finp.close();
	fout.close();
	return 0;
}
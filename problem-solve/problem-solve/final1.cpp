#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

ifstream finp("final1.inp");
ofstream fout("final1.out");

vector<int> arr;
vector<int> inp;

void solve(int temp) {

	for (int i = 2; i < temp; i++) {
		arr.push_back(arr[i - 1] + arr[i - 2] + 2);
	}

}

int main() {

	arr.push_back(1);
	arr.push_back(2);

	int k, temp = 0;
	finp >> k;
	while (k--) {
		int num;
		finp >> num;

		inp.push_back(num);
		if (temp < num) {
			temp = num;
		}

	}

	solve(temp);

	for (int i = 0; i < inp.size(); i++) {

		for (int j = 0; j < inp[i]; j++) {
			if (inp[i] <= arr[j]) {
				fout << arr[j-1] << '\n';
				break;
			}
			
		}

	}

	return 0;
}
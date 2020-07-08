#include <fstream>
#include <cstring>
#include <algorithm>
#define MAX 9999999 
using namespace std;

ifstream finp("color.inp");
ofstream fout("color.out");

int dp[5002][5002], acc1[5002][26], acc2[5002][26];
string str, str1;

int get_len(int len, int len1, int x, int y, int c) {
	int ret1 = 0, ret2 = 0;
	if (acc1[x][c] + acc2[y][c] == acc1[len - 1][c] + acc2[len1 - 1][c]) ret1 = x + y;
	if (acc1[x][c] + acc2[y][c] == 1) ret2 = x + y;
	return ret1 - ret2;
}

void get_acc(int len, int len1) {

	for (int i = 1; i < len; i++) {
		for (int j = 0; j < 26; j++) acc1[i][j] = acc1[i - 1][j];
		acc1[i][str[i] - 'A']++;
	}
	for (int i = 1; i < len1; i++) {
		for (int j = 0; j < 26; j++) acc2[i][j] = acc2[i - 1][j];
		acc2[i][str1[i] - 'A']++;
	}

}

void solve(int len, int len1) {
	
	get_acc(len, len1);

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len1; j++) {
			int ret1 = get_len(len, len1, i + 1, j, str[i + 1] - 'A');
			int ret2 = get_len(len, len1, i, j + 1, str1[j + 1] - 'A');
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + ret1);
			dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + ret2);
		}
	}

}

int main() {

	int testcase;
	finp >> testcase;

	while (testcase--) {

		string read;
		str.push_back('*');
		str1.push_back('*');
		finp >> read;
		str += read;
		int len = str.size();
		finp >> read;
		str1 += read;
		int len1 = str1.size();
		
		for (int i = 0; i < 5002; i++) {
			for (int j = 0; j < 5002; j++) {
				dp[i][j] = MAX;
			}
		}
		dp[0][0] = 0;

		memset(acc1, 0, sizeof(acc1));
		memset(acc2, 0, sizeof(acc2));

		solve(len, len1);

		fout << dp[len - 1][len1 - 1] << '\n';

		str.clear();
		str1.clear();

	}

	return 0;
}
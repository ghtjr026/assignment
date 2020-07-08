#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

ifstream finp("poker.inp");
ofstream fout("poker.out");

typedef struct card {

	char shape;
	int number;

};

vector<card> myCard;
int Shape[4], Num[14];

bool comp(const card& a, const card& b) {
	if (a.shape == b.shape) {
		return a.number < b.number;
	}
	else {
		return a.shape < b.shape;
	}
}

void counting(card& a) {

	switch (a.shape)
	{
	case 'S':
		Shape[0]++; break;
	case 'D':
		Shape[1]++; break;
	case 'H':
		Shape[2]++; break;
	case 'C':
		Shape[3]++; break;
	}

	Num[a.number]++;
	return;
}

void init() {

	for (int i = 0; i < 7; i++) {
		char s, n;
		finp >> s >> n;
		int num;
		switch (n)
		{
		case 'A':
			num = 1; break;
		case 'T':
			num = 10; break;
		case 'J':
			num = 11; break;
		case 'Q':
			num = 12; break;
		case 'K':
			num = 13; break;
		default:
			num = n - 48; break;
		}
		myCard.push_back( { s, num });
		counting(myCard[i]);
	}

	sort(myCard.begin(), myCard.end(), comp);

	return;
}

//4card Flush straight triple pair
bool straightFlush() {

	char s = 'A';
	int cnt = 0, k;
	for (k = 0; k < 4; k++) {
		if (Shape[k] >= 5) {
			if (k == 0) {
				s = 'S';
			}
			else if (k == 1) {
				s = 'D';
			}
			else if (k == 2) {
				s = 'H';
			}
			else {
				s = 'C';
			}
			break;
		}
	}
	if (s == 'A') {
		return false;
	}

	for (int i = 0; i < 7; i++) {
		if (myCard[i].shape == s) {
			int j;
			for (j = i; j < i + Shape[k] - 1; j++) {
				if (myCard[j].number + 1 == myCard[j + 1].number) {
					cnt++;
					if (cnt == 4) {
						return true;
					}
				}
				else {
					cnt = 0;
				}
			}
			if (cnt == 3) {
				if (myCard[i].number == 1 && myCard[j].number == 13) {
					return true;
				}
			}
			return false;
		}
	}
}

bool fourCard() {

	for (int i = 1; i < 14; i++) {
		if (Num[i] >= 4) {
			return true;
		}
	}
	return false;

}

bool fullHouse() {

	int tcnt = 0; bool flag = false;
	for (int i = 1; i < 14; i++) {
		if (Num[i] == 3) {
			tcnt++;
			flag = true;
		}
		else if (Num[i] >= 2) {
			tcnt++;
		}
	}
	if (flag && tcnt > 1) {
		return true;
	}
	return false;

}

bool Flush() {

	for (int i = 0; i < 4; i++) {
		if (Shape[i] >= 5) {
			return true;
		}
	}
	return false;

}

bool Straight() {

	int cnt = 0;
	for (int i = 1; i < 13; i++) {
		if (Num[i] >= 1 && Num[i + 1] >= 1) {
			cnt++;
		}
		else {
			cnt = 0;
		}
		if (cnt == 4) return true;
	}
	if (cnt == 3) {
		if (Num[13] >= 1 && Num[1] >= 1) {
			return true;
		}
	}
	return false;
}

void Mode() {

	int pairCnt = 0; bool flag = true;
	for (int i = 1; i < 14; i++) {
		if (Num[i] == 3) {
			fout << "Triple\n";
			flag = false;
			break;
		}
		else if (Num[i] == 2) {
			pairCnt++;
		}
	}
	if (flag) {
		if (pairCnt > 1) {
			fout << "Two Pair\n";
		}
		else if (pairCnt == 1) {
			fout << "One Pair\n";
		}
		else {
			fout << "Top\n";
		}
	}

}

void solve() {
	
	if (straightFlush()) {
		fout << "Straight Flush\n";
	}
	else if (fourCard()) {
		fout << "Four Card\n";
	}
	else if (fullHouse()) {
		fout << "Full House\n";
	}
	else if (Flush()) {
		fout << "Flush\n";
	}
	else if (Straight()) {
		fout << "Straight\n";
	}
	else {
		Mode();
	}
 
	return;
}

int main() {

	int testcase;
	finp >> testcase;
	while (testcase--) {
		
		init();
		solve();

		myCard.clear();
		memset(Shape, 0, sizeof(Shape));
		memset(Num, 0, sizeof(Num));
	}

	finp.close();
	fout.close();
	return 0;
}
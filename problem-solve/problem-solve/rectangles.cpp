#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

ifstream finp("rectangles.inp");
ofstream fout("rectangles.out");

typedef struct rec {

	int x, y, dy;
	char state;

}Rec;

vector<Rec> rec;
int cnt[20001], Min ,Max;

bool comp(Rec& a, Rec& b) {
	return a.x < b.x;
}

void findRange(int num) {
	Min = 30000;

	for (int i = 0; i < num * 2; i++) {
		//find min
		if (rec[i].y < Min) {
			Min = rec[i].y;
		}
		//find max
		if (rec[i].y > Max) {
			Max = rec[i].y;
		}
	}

}

void solve(int num) {

	int area = 0;

	for (int i = 0; i < rec.size() - 1;) {

		vector<Rec> range;
		while (1) {
			if (rec[i].x != rec[i + 1].x) break;
			range.push_back(rec[i++]);
		}
		range.push_back(rec[i++]);	
		for (int j = 0; j < range.size(); j++) {

			if (range[j].state == 'l') {
				for (int k = range[j].y; k < range[j].dy; k++) {
					cnt[k]++;
				}
			}
			if (range[j].state == 'r') {
				for (int k = range[j].dy; k < range[j].y; k++) {
					cnt[k]--;
				}
			}
		}

		int Size = 0;
		for (int j = Min; j < Max + 1; j++) {
			if (cnt[j] > 0) Size++;
		}
		area += Size * (rec[i].x - rec[i - 1].x);

	}

	fout << area << '\n';

}

int main() {

	int num;
	finp >> num;

	rec.resize(num * 2);
	for (int i = 0; i < num; i++) {

		int x, y, x1 ,y1;
		finp >> x >> y >> x1 >> y1;
		rec[i] = { x + 10000,y + 10000, y1 + 10000, 'l' }; 
		rec[i + num] = { x1 + 10000,y1 + 10000, y + 10000, 'r' }; 

	}

	sort(rec.begin(), rec.end(), comp);
	findRange(num);
	solve(num);
	

	return 0;
}

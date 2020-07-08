#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

typedef struct Rec {
	long long x, y;
	char side;
}Rec;

struct cmp {
	bool operator()(const Rec& a, const Rec& b) {

		if (a.x < b.x) {
			return true;
		}
		return false;

	}
};

ifstream finp("contour.inp");
ofstream fout("contour.out");

vector<Rec> rec;
set<long long> cnt;
long long set[1000001];
cmp comp;

void solve() {

	long long area = 0;

	for (int i = 0; i < rec.size(); i++) {
		
			if (!cnt.empty()) {
				area += (rec[i].x - rec[i - 1].x) * (*(--cnt.end()));
			}
			if (rec[i].side == 'L') {
				cnt.insert(rec[i].y);
				set[rec[i].y]++;
			}
			if (rec[i].side == 'R') {
				set[rec[i].y]--;
				if (set[rec[i].y] == 0) {
					cnt.erase(rec[i].y);
				}
				if (cnt.empty() && area) {
					fout << area << ' ';
					area = 0;
				}
			
		}

	}
	fout << '\n';

}

int main() {

	int t = 1;
	while (1) {

		int x = -1, h = -1, x1 = -1;
		finp >> x >> h >> x1;

		if (x == -1) break;
		if (x == 0 && h == 0 && x1 == 0) {
			fout << "Test Case #" << t << " : ";
			printf("%d", t);
			t++;
			sort(rec.begin(), rec.end(), comp);
			solve();
			rec.clear();
		}
		else {
			rec.push_back({ x,h,'L' });
			rec.push_back({ x1,h,'R' });
		}

	}

	return 0;
}
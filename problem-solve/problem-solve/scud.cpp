#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

ifstream finp("scud.inp");
FILE* fout = fopen("scud.out", "wt");

typedef struct Kingdom {

	int x, y;
	int p, q;
	Kingdom() : x(0), y(0), p(1), q(0) {}
	Kingdom(int x1, int y1) : x(x1), y(y1), p(1), q(0) {}

}Kingdom;

vector<vector<Kingdom>> Wall;
vector<Kingdom> kingdom;
vector<bool> distroy;

bool comp(const Kingdom& A, const Kingdom& B) {
	if (1LL * A.q * B.p != 1LL * A.p * B.q)
		return 1LL * A.q * B.p < 1LL * A.p * B.q;
	if (A.x != B.x) return A.x < B.x;
	return A.y < B.y;
}

long long ccw(const Kingdom& A, const Kingdom& B, const Kingdom& C) {
	return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (B.y - A.y) * (C.x - A.x);
}

bool leftturn(Kingdom a, Kingdom b, Kingdom c) {
	return ccw(a, b, c) > 0;
}

bool collinear(Kingdom a, Kingdom b, Kingdom c) {
	return ccw(a, b, c) == 0;
}

bool between(Kingdom a, Kingdom b, Kingdom c) {

	if (!collinear(a, b, c)) {
		return false;
	}
	if (a.x != b.x) {
		return a.x <= c.x && c.x <= b.x || b.x <= c.x && c.x <= a.x;
	}
	else {
		return a.y <= c.y && c.y <= b.y || b.y <= c.y && c.y <= a.y;
	}

}

vector<Kingdom> convwxhell(vector<Kingdom> &kingdom) {

	sort(kingdom.begin(), kingdom.end(), comp);

	for (int i = 1; i < kingdom.size(); i++) {
		kingdom[i].p = kingdom[i].x - kingdom[0].x;
		kingdom[i].q = kingdom[i].y - kingdom[0].y;
	}

	sort(kingdom.begin() + 1, kingdom.end(), comp);

	vector<int> s;

	s.push_back(0);
	s.push_back(1);

	int next = 2;

	while (next < kingdom.size()) {

		while (s.size() >= 2) {
			int first, second;
			second = s.back();
			s.pop_back();
			first = s.back();

			if (ccw(kingdom[first], kingdom[second], kingdom[next]) > 0) {
				s.push_back(second);
				break;
			}

		}
		s.push_back(next);
		next++;
	}

	vector<Kingdom> wallPoint;
	for (int i = 0; i < s.size(); i++) {
		wallPoint.push_back(kingdom[s[i]]);
	}
	return wallPoint;

}

int inaLocation(vector<Kingdom> &kingdom, Kingdom pivot) {

	int crossing = 0;

	for (int i = 0; i < kingdom.size(); i++) {
		int ipuls1 = (i + 1) % kingdom.size();

		if (between(kingdom[i], kingdom[ipuls1], pivot)) {
			return 1;
		}if ((kingdom[i].y < pivot.y && kingdom[ipuls1].y >= pivot.y && leftturn(kingdom[i], kingdom[ipuls1], pivot))
			|| kingdom[ipuls1].y < pivot.y && kingdom[i].y >= pivot.y && leftturn(kingdom[ipuls1], kingdom[i], pivot)) {
			crossing++;
		}

	}

	return crossing % 2;

}

double getArea(vector<Kingdom> &kingdom) {

	double result = 0.0;
	for (int i = 0; i < kingdom.size(); i++) {

		result += (kingdom[i].x * kingdom[(i + 1) % kingdom.size()].y);
		result -= (kingdom[(i + 1) % kingdom.size()].x * kingdom[i].y);

	}
	return fabs(result/2);
	
}

int main() {

	int num;
	while (finp >> num) {

		if (num == -1) {
			break;
		}

		for (int i = 0; i < num; i++) {
			
			int x, y;
			finp >> x >> y;
			kingdom.push_back(Kingdom(x, y));

		}
		Wall.push_back(convwxhell(kingdom));
		kingdom.clear();
		distroy.push_back(false);

	}

	int x, y;
	double area = 0;

	while (finp >> x >> y) {

		for (int i = 0; i < Wall.size(); i++) {
			if (!distroy[i]) {
				if (inaLocation(Wall[i], { x,y })) {
					distroy[i] = true;
					area += getArea(Wall[i]);
					break;
				}
			}
		}

	}

	//for (int i = 0; i < missile.size(); i++) {

	//	for (int j = 0; j < Wall.size();j++){

	//		if (inaLocation(Wall[j], missile[i])) {
	//			area += getArea(Wall[j]);
	//			break;
	//		}

	//	}

	//}

	fprintf(fout, "%.2lf\n", area);

}

#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#pragma warning (disable : 4996)
using namespace std;

ifstream finp("tangent.inp");
FILE* fout = fopen("tangent.out", "wt");

typedef struct Point {

	long long x, y;
	long long p, q;
	int number;
	char sector;
	Point() : x(0), y(0), p(1), q(0), sector() {}
	Point(int x1, int y1) : x(x1), y(y1), p(1), q(0), sector() {}

}Point;

vector<Point> P, Q, total, hull, Inner;
vector<int> s;
int ptop, pbottom, qtop, qbottom;

bool comp(const Point& A, const Point& B) {
	if (1LL * A.q * B.p != 1LL * A.p * B.q) {
		return 1LL * A.q * B.p < 1LL * A.p * B.q;
	}
	if (A.x != B.x) {
		return A.x < B.x;
	}
	return A.y < B.y;
}

long long ccw(const Point& pivot, const Point& A, const Point& B) {
	return 1LL * (A.x - pivot.x) * (B.y - pivot.y) - 1LL * (A.y - pivot.y) * (B.x - pivot.x);
}

void convexHull(int totalpoint) {

	s.push_back(0);
	s.push_back(1);
	int next = 2;
	while (next < totalpoint) {

		while (s.size() >= 2) {
			int first, second;
			first = s.back(); s.pop_back();
			second = s.back();

			if (ccw(total[second], total[first], total[next]) > 0) {
				s.push_back(first);
				break;
			}
		}
		s.push_back(next);
		next++;
	}

}

long long getDirection(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void findPoint() {

	for (int i = 0; i < s.size(); i++) {
		int ipuls1 = (i + 1) % s.size();
		Point Pre = total[s[i]], next = total[s[ipuls1]];

		if (Pre.sector == 'p' && next.sector == 'q') {
			pbottom = Pre.number; qbottom = next.number;

			for (int j = 0; j < P.size(); j++) {
				if (ccw(Pre, P[j], next) == 0) {
					if (getDirection(P[j], next) < getDirection(Pre, next)) {
						pbottom = P[j].number; Pre = P[j];
					}
				}
			}

			for (int j = 0; j < Q.size(); j++) {
				if (ccw(Pre, Q[j], next) == 0) {
					if (getDirection(Pre, Q[j]) < getDirection(Pre, next)) {
						qbottom = P[j].number; next = Q[j];
					}
				}
			}

		}
		else if (Pre.sector == 'q' && next.sector == 'p') {
			qtop = Pre.number; ptop = next.number;

			for (int j = 0; j < Q.size(); j++) {
				if (ccw(Pre, Q[j], next) == 0) {
					if (getDirection(next, Q[j]) < getDirection(next, Pre)) {
						qtop = Q[j].number; Pre = Q[j];
					}
				}
			}
			for (int j = 0; j < P.size(); j++) {
				if (ccw(Pre, P[j], next) == 0) {
					if (getDirection(next, P[j]) < getDirection(next, Pre)) {
						ptop = P[j].number; next = P[j];
					}
				}
			}
		}

	}

}

void makeInner() {

	for (int i = pbottom; ; i = (i + 1) % P.size()) {

		Inner.push_back(P[i]);
		if (i == ptop) {
			break;
		}

	}

	for (int i = qtop; ; i = (i + Q.size() + 1) % Q.size()) {

		Inner.push_back(Q[i]);
		if (i == qbottom) {
			break;
		}

	}

}

void getArea() {

	double result = 0.0;

	for (int i = 0; i < Inner.size(); i++) {

		result += Inner[i].x * Inner[(i + 1) % Inner.size()].y - Inner[(i + 1) % Inner.size()].x * Inner[i].y;

	}

	if (ptop == pbottom) {
		for (int i = 0; i < P.size(); i++) {

			result += P[i].x * P[(i + 1) % P.size()].y - P[(i + 1) % P.size()].x * P[i].y;

		}
	}
	else if (qtop == qbottom) {
		for (int i = 0; i < Q.size(); i++) {

			result += Q[i].x * Q[(i + 1) % Q.size()].y - Q[(i + 1) % Q.size()].x * Q[i].y;

		}
	}

	result = fabs(result / 2);

	fprintf(fout,"%.1lf\n",result);

}

int main() {

	int testcase;
	finp >> testcase;
	while (testcase--) {
		int p, q;
		finp >> p;
		for (int i = 0; i < p; i++) {
			int x, y;
			finp >> x >> y;
			P.push_back({ x,y });
			P[i].sector = 'p';
			P[i].number = i;
		}
		finp >> q;
		for (int i = 0; i < q; i++) {
			int x, y;
			finp >> x >> y;
			Q.push_back({ x,y });
			Q[i].sector = 'q';
			Q[i].number = i;
		}

		//convexhull 하기전 모든 점을 합침
		for (int i = 0; i < P.size(); i++) {
			total.push_back(P[i]);
		}
		for (int i = 0; i < Q.size(); i++) {
			total.push_back(Q[i]);
		}

		sort(total.begin(), total.end(), comp);
		for (int i = 1; i < total.size(); i++) {
			total[i].p = total[i].x - total[0].x;
			total[i].q = total[i].y - total[0].y;
		}
		sort(total.begin() + 1, total.end(), comp);

		//convexhull된 점들을 찾음 인덱스로
		convexHull(total.size());

		//도형 x의 점 찾기
		findPoint();
		makeInner();
		getArea();

		P.clear();
		Q.clear();
		total.clear();
		s.clear();
		hull.clear();
		Inner.clear();
	}

	return 0;
}
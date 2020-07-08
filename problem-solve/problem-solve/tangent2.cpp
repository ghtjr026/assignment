#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#pragma warning (disable : 4996)
using namespace std;

ifstream finp("tangent2.inp");
FILE* fout = fopen("tangent2.out", "wt");

typedef struct Point {

	long long x, y;
	long long p, q;
	int number;
	char sector;
	Point() : x(0), y(0), p(1), q(0), sector() {}
	Point(int x1, int y1) : x(x1), y(y1), p(1), q(0), sector() {}

}Point;

vector<Point> P, Q, total, phull, qhull, Inner;
vector<int> s, ps, qs;
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

void convexHullP(int totalpoint) {

	ps.push_back(0);
	ps.push_back(1);
	int next = 2;
	while (next < totalpoint) {

		while (ps.size() >= 2) {
			int first, second;
			first = ps.back(); ps.pop_back();
			second = ps.back();

			if (ccw(phull[second], phull[first], phull[next]) > 0) {
				ps.push_back(first);
				break;
			}
		}
		ps.push_back(next);
		next++;
	}

}

void convexHullQ(int totalpoint) {

	qs.push_back(0);
	qs.push_back(1);
	int next = 2;
	while (next < totalpoint) {

		while (qs.size() >= 2) {
			int first, second;
			first = qs.back(); qs.pop_back();
			second = qs.back();

			if (ccw(qhull[second], qhull[first], qhull[next]) > 0) {
				qs.push_back(first);
				break;
			}
		}
		qs.push_back(next);
		next++;
	}

}

long long getDirection(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void findPtoQ() {

	while (1) {
		bool flagP = false, flagQ = false;
		for (int i = 0; i < ps.size(); i++) {
			if (ccw(qhull[qs[qbottom]], phull[ps[i]], phull[ps[ptop]]) > 0) {
				flagP = true;
				ptop = (ptop + ps.size() - 1) % ps.size();
				break;
			}
		}

		for (int i = 0; i < qs.size(); i++) {
			if (ccw(phull[ps[ptop]], qhull[qs[i]], qhull[qs[qbottom]]) > 0) {
				flagQ = true;
				qbottom = (qbottom + qs.size() - 1) % qs.size();
				break;
			}
		}
		
		if (!flagP && !flagQ) {
			break;
		}
	}

	for (int i = 0; i < ps.size(); i++) {
		if (ccw(phull[ps[ptop]], phull[ps[i]], qhull[qs[qbottom]]) == 0) {
			if (getDirection(phull[ps[i]], qhull[qs[qbottom]]) < getDirection(phull[ps[ptop]], qhull[qs[qbottom]])) {
				ptop = i;
			}
		}
	}
	for (int i = 0; i < qs.size(); i++) {
		if (ccw(qhull[qs[qbottom]], qhull[qs[i]], phull[ps[ptop]]) == 0) {
			if (getDirection(qhull[qs[i]], phull[ps[ptop]]) < getDirection(qhull[qs[qbottom]], phull[ps[ptop]])) {
				qbottom = i;
			}
		}
	}

}

void findQtoP() {

	while (1) {
		bool flagP = false, flagQ = false;
		for (int i = 0; i < ps.size(); i++) {
			if (ccw(qhull[qs[qtop]], phull[ps[i]], phull[ps[pbottom]]) < 0) {
				flagP = true;
				pbottom = (pbottom + 1) % ps.size();
				break;
			}
		}

		for (int i = 0; i < qs.size(); i++) {
			if (ccw(phull[ps[pbottom]], qhull[qs[i]], qhull[qs[qtop]]) < 0) {
				flagQ = true;
				qtop = (qtop + 1) % qs.size();
				break;
			}
		}
		if (!flagP && !flagQ) {
			break;
		}

	}

	for (int i = 0; i < ps.size(); i++) {
		if (ccw(phull[ps[pbottom]], phull[ps[i]], qhull[qs[qtop]]) == 0) {
			if (getDirection(phull[ps[i]], qhull[qs[qtop]]) < getDirection(phull[ps[pbottom]], qhull[qs[qtop]])) {
				pbottom = i;
			}
		}
	}
	for (int i = 0; i < qs.size(); i++) {
		if (ccw(qhull[qs[qtop]], qhull[qs[i]], phull[ps[pbottom]]) == 0) {
			if (getDirection(qhull[qs[i]], phull[ps[pbottom]]) < getDirection(qhull[qs[qtop]], phull[ps[pbottom]])) {
				qtop = i;
			}
		}
	}
}

void findPoint() {

	for (int i = 0; i < s.size(); i++) {
		int ipuls1 = (i + 1) % s.size();
		Point Pre = total[s[i]], next = total[s[ipuls1]];

		if (Pre.sector == 'p' && next.sector == 'q') {
			pbottom = Pre.number; qbottom = next.number;
		}
		else if (Pre.sector == 'q' && next.sector == 'p') {
			qtop = Pre.number; ptop = next.number;
		}

	}

	for (int i = 0; i < ps.size(); i++) {
		if (phull[ps[i]].number == ptop) {
			ptop = i;
		}
		else if (phull[ps[i]].number == pbottom) {
			pbottom = i;
		}
	}
	for (int i = 0; i < qs.size(); i++) {
		if (qhull[qs[i]].number == qtop) {
			qtop = i;
		}
		else if (qhull[qs[i]].number == qbottom) {
			qbottom = i;
		}
	}

	findPtoQ();
	findQtoP();

}

void makeInner() {

	for (int i = phull[ps[pbottom]].number; ; i = (i + 1) % phull.size()) {

		Inner.push_back(P[i]);
		if (i == phull[ps[ptop]].number) {
			break;
		}

	}

	for (int i = qhull[qs[qtop]].number; ; i = (i + qhull.size() + 1) % qhull.size()) {

		Inner.push_back(Q[i]);
		if (i == qhull[qs[qbottom]].number) {
			break;
		}

	}

}

void getArea() {

	double result = 0.0;

	for (int i = 0; i < Inner.size(); i++) {

		result += (Inner[i].x * Inner[(i + 1) % Inner.size()].y) - (Inner[(i + 1) % Inner.size()].x * Inner[i].y);

	}

	result = fabs(result / 2);

	fprintf(fout, "%.1lf\n", result);

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

		//convexhull 하기전 정렬
		sort(total.begin(), total.end(), comp);
		for (int i = 1; i < total.size(); i++) {
			total[i].p = total[i].x - total[0].x;
			total[i].q = total[i].y - total[0].y;
		}
		sort(total.begin() + 1, total.end(), comp);

		phull = P; qhull = Q;

		sort(phull.begin(), phull.end(), comp);
		for (int i = 1; i < phull.size(); i++) {
			phull[i].p = phull[i].x - phull[0].x;
			phull[i].q = phull[i].y - phull[0].y;
		}
		sort(phull.begin() + 1, phull.end(), comp);

		sort(qhull.begin(), qhull.end(), comp);
		for (int i = 1; i < qhull.size(); i++) {
			qhull[i].p = qhull[i].x - qhull[0].x;
			qhull[i].q = qhull[i].y - qhull[0].y;
		}
		sort(qhull.begin() + 1, qhull.end(), comp);

		//convexhull된 점들을 찾음 인덱스로
		convexHull(total.size());
		convexHullP(phull.size());
		convexHullQ(qhull.size());

		//도형 x의 점 찾기
		findPoint();
		makeInner();
		getArea();

		P.clear(); Q.clear(); total.clear();
		phull.clear(); qhull.clear();
		s.clear(); ps.clear(); qs.clear();
		Inner.clear();
	}

	return 0;
}
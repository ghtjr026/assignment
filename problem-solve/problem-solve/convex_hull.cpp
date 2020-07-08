#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream finp("convex_hull.inp");
ofstream fout("convex_hull.out");


typedef struct Point {
	
	int x, y;
	int p, q;
	Point() : x(0), y(0), p(1), q(0) {}
	Point(int x1, int y1) : x(x1), y(y1), p(1), q(0) {}

}Point;

vector<Point> point;

bool comp(const Point& A, const Point& B) {
	if (1LL * A.q * B.p != 1LL * A.p * B.q)
		return 1LL * A.q * B.p < 1LL * A.p * B.q;
	if (A.x != B.x) return A.x < B.x;
	return A.y < B.y;
}

long long ccw(const Point& A, const Point& B, const Point& C) {
	return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (B.y - A.y) * (C.x - A.x);
}

void solve(int totalpoint) {

	vector<int> s;

	s.push_back(0);
	s.push_back(1);

	int next = 2;

	while (next < totalpoint) {

		while (s.size() >= 2) {
			int first, second;
			first = s.back();
			s.pop_back();
			second = s.back();

			if (ccw(point[second], point[first], point[next]) > 0) {
				s.push_back(first);
				break;
			}	

		}
		s.push_back(next);
		next++;
	}

	fout << s.size() << '\n';

	for (int i = 0; i < s.size(); i++) {
		fout << point[s[i]].x << ' ' << point[s[i]].y << '\n';
	}

}


int main() {

	int totalpoint;
	finp >> totalpoint;

	while (totalpoint--) {
		int x, y;
		finp >> x >> y;
		point.push_back(Point(x, y));
	}

	sort(point.begin(), point.end(), comp);

	for (int i = 1; i < point.size(); i++) {
		point[i].p = point[i].x - point[0].x;
		point[i].q = point[i].y - point[0].y;
	}

	sort(point.begin() + 1, point.end(), comp);

	solve(point.size());

	return 0;
}
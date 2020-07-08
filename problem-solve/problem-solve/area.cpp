#include <fstream>
#include <cstdio>
#include <vector>
#include <cmath>
#pragma warning(disable : 4996)
using namespace std;

ifstream finp("area.inp");
FILE* fout = fopen("area.out", "wt");

typedef struct circle {

	int x, y, r;

}circle;

typedef struct point {
	
	double x, y;

}point;

vector<circle> Circle;
vector<point> Point;

bool innerCircle(circle& C, double ix, double iy) {

	if (sqrt(((C.x - ix) * (C.x - ix)) + ((C.y - iy) * (C.y - iy))) < C.r) return true;
	else return false;

}

void getPoint(circle &A, circle &B, circle &C) {

	double dis = sqrt(((A.x - B.x) * (A.x - B.x)) + ((A.y - B.y) * (A.y - B.y)));
	// 두 원점사이의 거리
	
	double tangent = ((A.r * A.r) - (B.r * B.r) + (dis * dis)) / (2 * dis); 
	// A원점과 접선 사이의 거리
	
	double height = sqrt((A.r * A.r) - (tangent * tangent)); 
	// 접선에서 교점과 두 원점사이의 직선의 거리
	
	double x = A.x + (tangent * (B.x - A.x) / dis) + (height * (B.y - A.y) / dis);
	// intersection x(두 원의 교점)
	
	double y = A.y + (tangent * (B.y - A.y) / dis) - (height * (B.x - A.x) / dis);
	// intersection y(두 원의 교점)

	if (!innerCircle(C, x, y)) {
		
		x = A.x + (tangent * (B.x - A.x) / dis) - (height * (B.y - A.y) / dis);
		y = A.y + (tangent * (B.y - A.y) / dis) + (height * (B.x - A.x) / dis);

	}

	Point.push_back({ x, y });

}

double getArea() {

	double result = 0;

	for (int i = 0; i < 3; i++) {
		result += Point[i].x * Point[(i + 1) % 3].y;
	}

	for (int i = 0; i < 3; i++) {
		result -= Point[i].x * Point[(i + 2) % 3].y;
	}

	return fabs(result / 2);

}

int main() {

	int testcase;
	finp >> testcase;
	
	while (testcase--) {

		int x, y, r;
		for (int i = 0; i < 3; i++) {
			finp >> x >> y >> r;
			Circle.push_back({ x,y,r });
		}

		getPoint(Circle[0], Circle[1], Circle[2]);
		getPoint(Circle[1], Circle[2], Circle[0]);
		getPoint(Circle[2], Circle[0], Circle[1]);

		fprintf(fout, "%.2lf\n", getArea());
		Circle.clear(); Point.clear();
	}

	return 0;
}
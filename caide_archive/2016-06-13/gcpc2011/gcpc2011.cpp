#include "Head.h"
#include "maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111111;

bool doubleEqual(double a, double b) // сравниваем на равенство с eps, константой 1е-9 используется только здесь
{
	return fabs(a - b) < 1e-9;
}


bool doubleLessOrEqual(double a, double b) // <= с eps
{
	return a < b || doubleEqual(a, b);
}


bool doubleLess(double a, double b) // < с eps
{
	return a < b && !doubleEqual(a, b);
}


bool doubleGreaterOrEqual(double a, double b) // >= с eps
{
	return a > b || doubleEqual(a, b);
}


bool doubleGreater(double a, double b) // > с eps
{
	return a > b && !doubleEqual(a, b);
}

double mySqrt(double a) // mySqrt с проверкой, что корректен аргумент
{
	if (doubleLess(a, 0)) //некорректный вызов
	{
		throw "sqrt(-1)";
	}
	if (a < 0) return 0; //отрицательное ввиду небольшой погрешности
	return sqrt(a);
}

template<typename T>
class Point2D {
public:

	Point2D() : Point2D(0, 0) {}
	Point2D(const T x, const T y) : x_(x), y_(y) {}

	T sqr_dist(const Point2D& rhs) const {
		return sqr(x_ - rhs.x_) + sqr(y_ - rhs.y_);
	}

	double dist(const Point2D& rhs) const {
		return sqrt(sqr_dist(rhs));
	}

	friend istream& operator >>(istream& in, Point2D& point) {
		in >> point.x_ >> point.y_;
		return in;
	}

	T x() const {
		return x_;
	}

	T y() const {
		return y_;
	}

	bool operator <(const Point2D& rhs) const {
		return x_ < rhs.x_ || (abs(x_ - rhs.x_) < EPS && y_ < rhs.y_);
	}

	Point2D operator *(const double rhs) const {
		return{ x_ * rhs, y_ * rhs };
	}

	Point2D operator +(const Point2D& rhs) const {
		return{ x_ + rhs.x_, y_ + rhs.y_ };
	}

	double length() const {
		return mySqrt(sqr(x_) + sqr(y_));
	}

	double scalar(const Point2D& rhs) const {
		return x_ * rhs.x_ + y_ * rhs.y_;
	}

	double cos_angle(const Point2D& rhs) const {
		return scalar(rhs) / (length() * rhs.length());
	}

	Point2D normalize(double k = 1) const {
		double len = length();
		if (doubleEqual(len, 0)) {
			if (doubleEqual(k, 0)) {
				return Point2D();
			}
			assert(false); // zero length
		}
		return *this * (k / len);
	}

	Point2D rotate() const {
		return Point2D(-y_, x_);
	}

	Point2D rotate(double alpha) const {
		return rotate(cos(alpha), sin(alpha));
	}

	Point2D rotate(double cosa, double sina) const {
		Point2D v = *this;
		Point2D u = v.rotate(); // вектор, перпендикулярный v, теперь (v, u) - базис, в котором мы знаем ответ
		Point2D w = v * cosa + u * sina; // зная координаты в базисе (v, u), нашли w
		return w;
	}

	Point2D operator -(const Point2D& rhs) const {
		return{ x_ - rhs.x_, y_ - rhs.y_ };
	}

private:
	T x_;
	T y_;

};

using Point = Point2D<double>;
using Vector = Point;

class Circle {
public:
	Circle() = default;

	Circle(const Point& o, const double r) : center_(o), radius_(r) {}

	friend istream& operator >>(istream& in, Circle& rhs) {
		in >> rhs.center_ >> rhs.radius_;
		return in;
	}

	Point center() const {
		return center_;
	}

	double radius() const {
		return radius_;
	}

private:
	Point center_;
	double radius_;

};

Point2D<double> leftmost(const Circle& circle) {
	return{ circle.center().x() - circle.radius(), circle.center().y() };
}

size_t find_leftmost(const std::vector<Circle>& circles) {
	size_t best = 0;
	for (size_t i = 1; i < circles.size(); ++i) {
		if (leftmost(circles[i]) < leftmost(circles[best])) {
			best = i;
		}
	}
	return best;
}

int getTangent(const Point& A, const Circle& circle, Vector& M, Vector& N) {
	Vector v = circle.center() - A;
	double d = v.length();
	if (doubleLess(d, circle.radius())) {
		return 0;
	}
	double alpha = asin(circle.radius() / d); // нашли угол между касательной и вектором v
	double L = mySqrt(sqr(d) - sqr(circle.radius())); // длина касательной
	v = v.normalize(L); // теперь v имеет длину касательной
	M = A + v.rotate(alpha);
	N = A - v.rotate(alpha);
	if (doubleEqual(circle.radius(), d)) return 1;
	return 2;
}

void getOutTangent(Circle A, Circle B, pair<Point, Point>& P, pair<Point, Point>& Q) {
	bool swapped = false;
	if (A.radius() > B.radius()) {
		swap(A, B);
		swapped = true;
	}
	Point u = (A.center() - B.center()).rotate(asin(A.radius() / A.center().dist(B.center()))).rotate().normalize(A.radius());
	P.first = A.center() + u;
	Q.first = A.center() - u;
	Vector T1, T2;
	getTangent(A.center(), Circle(B.center(), B.radius() - A.radius()), T1, T2); //сжали окружности на rA , получили ответ для неё, потом раздвинули прямые на rA в стороны
	P.second = T1 + u;
	Q.second = T2 - u;
	if (swapped) {
		swap(P, Q);
	}
}

void solve(istream& in, ostream& out) {
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		in >> n;
		vector<Circle> circles(n);
		in >> circles;
		const size_t start = find_leftmost(circles);
		std::vector<bool> used(n, false);
		size_t cur = start;
		std::vector<Circle> path;
		while (true) {
			path.emplace_back(circles[cur]);
			used[cur] = true;
			Vector base(0, -1);
			double mx = -INF;
			for (size_t i = 0; i < circles.size(); ++i) {
				if (i == cur) {
					continue;
				}
				pair<Point, Point> a, b;
				getOutTangent(circles[cur], circles[i], a, b);
				
			}
		}
	}
}
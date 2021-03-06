#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

class Vec2 {
public:
	using type = double;
	using reference = type&;
	using const_reference = const type&;
	using container = std::vector<type>;

	Vec2() : Vec2({ 0, 0 }) {}
	Vec2(const std::initializer_list<type>& args) : data_(args) {}

	Vec2(const Vec2&) = default;
	Vec2& operator =(const Vec2&) = default;
	Vec2(Vec2&&) = default;
	Vec2& operator =(Vec2&&) = default;

	const_reference operator [](const size_t index) const {
		return data_[index];
	}

	reference operator [](const size_t index) {
		return data_[index];
	}

	const size_t size() const {
		return 2;
	}

	Vec2 operator +(const Vec2& rhs) const {
		return{ data_[0] + rhs[0], data_[1] + rhs[1] };
	}

	Vec2 operator -(const Vec2& rhs) const {
		return{ data_[0] - rhs[0], data_[1] - rhs[1] };
	}

	friend std::ostream& operator << (std::ostream& out, const Vec2& rhs) {
		out << "{" << rhs[0] << ", " << rhs[1] << "}";
		return out;
	}

private:
	container data_;
};

class Matrix2x2 {
public:
	using type = double;
	using row_storage = Vec2;
	using container = std::vector<row_storage>;
	using row_reference = row_storage&;
	using row_const_reference = const row_storage&;

	Matrix2x2() : Matrix2x2({ { 0, 0 },{ 0, 0 } }) {}
	Matrix2x2(const std::initializer_list<row_storage>& args) : data_(args) {}

	Matrix2x2(const Matrix2x2& rhs) : data_(rhs.data_) {}
	Matrix2x2& operator =(const Matrix2x2&) = default;
	Matrix2x2(Matrix2x2&& rhs) : data_(std::move(rhs.data_)) {}
	Matrix2x2& operator =(Matrix2x2&&) = default;

	const size_t size() const {
		return 2;
	}

	row_const_reference operator [] (const size_t index) const {
		return data_[index];
	}

	row_reference operator [] (const size_t index) {
		return data_[index];
	}

	Vec2 operator * (const Vec2& v) const {
		return{ data_[0][0] * v[0] + data_[0][1] * v[1], data_[1][0] * v[0] + data_[1][1] * v[1] };
	}

	Matrix2x2 operator * (const Matrix2x2& v) const {
		return{ { data_[0][0] * v[0][0] + data_[0][1] * v[1][0], data_[0][0] * v[0][1] + data_[0][1] * v[1][1] },
		{ data_[1][0] * v[0][0] + data_[1][1] * v[1][0], data_[1][0] * v[0][1] + data_[1][1] * v[1][1] } };
	}

	Matrix2x2 operator + (const Matrix2x2& rhs) const {
		return{ data_[0] + rhs[0], data_[1] + rhs[1] };
	}

	Matrix2x2 operator - (const Matrix2x2& rhs) const {
		return{ data_[0] - rhs[0], data_[1] - rhs[1] };
	}

	double det() {
		return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
	}

	Matrix2x2 inverse() const {
		Matrix2x2 res;
		double d = data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
		res[0][0] = data_[1][1] / d;
		res[0][1] = -data_[0][1] / d;
		res[1][0] = -data_[1][0] / d;
		res[1][1] = data_[0][0] / d;
		return res;
	}

	Matrix2x2 operator ~ () const {
		return inverse();
	}

	friend std::ostream& operator << (std::ostream& out, const Matrix2x2& rhs) {
		out << "{" << std::endl << "  " << rhs[0] << "," << std::endl << "  " << rhs[1] << std::endl << "}";
		return out;
	}

private:
	container data_;
};

double f(double x1, double y1, double x2, double y2, double x, double y, double a) {
	return sqrt(sqr(x1 - x) + sqr(y1 - y))*sqrt(sqr(x2 - x) + sqr(y2 - y)) * cos(a) - (x1 - x)*(x2 - x) - (y1 - y)*(y2 - y);
}

double dfdx(double x1, double y1, double x2, double y2, double x, double y, double a) {
	return ((x - x1) / sqrt(sqr(x1 - x) + sqr(y1 - y))*sqrt(sqr(x2 - x) + sqr(y2 - y))
		+ (x - x2) / sqrt(sqr(x2 - x) + sqr(y2 - y))*sqrt(sqr(x1 - x) + sqr(y1 - y))
		)* cos(a)
		- (2 * x - x1 - x2);
}

double dfdy(double x1, double y1, double x2, double y2, double x, double y, double a) {
	return ((y - y1) / sqrt(sqr(x1 - x) + sqr(y1 - y))*sqrt(sqr(x2 - x) + sqr(y2 - y))
		+ (y - y2) / sqrt(sqr(x2 - x) + sqr(y2 - y))*sqrt(sqr(x1 - x) + sqr(y1 - y))
		)* cos(a)
		- (2 * y - y1 - y2);
}


void solve(istream& ins, ostream& out) {
	int n;
	ins >> n;
	for (__ = 0; __ < n; __++) {
		double x[4], y[4], a1, a2;
		for (int i = 0; i < 3; ++i) {
			ins >> x[i] >> y[i];
		}
		ins >> a1 >> a2;
		a1 *= M_PI / 180;
		a2 *= M_PI / 180;

		Vec2 ans = { -100000.5,-100000.5 }, dans, vecf;
		Matrix2x2 df;
		int ii = 0;
		while (ii<100) {
			vecf = { -f(x[0],y[0],x[1],y[1],ans[0],ans[1],a1),-f(x[1],y[1],x[2],y[2],ans[0],ans[1],a2) };
			df = { { dfdx(x[0],y[0],x[1],y[1],ans[0],ans[1],a1), dfdy(x[0],y[0],x[1],y[1],ans[0],ans[1],a1) },
			{ dfdx(x[1],y[1],x[2],y[2],ans[0],ans[1],a2) ,dfdy(x[1],y[1],x[2],y[2],ans[0],ans[1],a2) } };
			dans = (~df) * vecf;
			if (sqrt(dans[0]* dans[0] + dans[1] * dans[1])< 1e-15)
			{
				break;
			}
			ans = ans + dans;
		}
		vecf = { -f(x[0],y[0],x[1],y[1],ans[0],ans[1],a1),-f(x[1],y[1],x[2],y[2],ans[0],ans[1],a2) };
		a1 =  ((x[0] - ans[0])*(x[1] - ans[0]) - (y[0] - ans[1])*(y[1] - ans[1]))/ (sqrt(sqr(x[0] - ans[0]) + sqr(y[0] - ans[1]))*sqrt(sqr(x[1] - ans[0]) + sqr(y[1] - ans[1])));
		out << fixed << setprecision(16) << ans[0] << " " << ans[1] << ' ' <<a1<< endl;
	}
}

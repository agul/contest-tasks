#include "base/header.hpp"

const int MOD = 1000000007;
const int MAXN = 111111;

using namespace std;

class Point {
public:
	int x, y;

	Point() : Point(0, 0) {}
	Point(int x, int y) : x(x), y(y) {}

	Point& operator-=(const Point& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	bool operator ==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	friend ostream& operator << (ostream& out, const Point& rhs) {
		out << rhs.x << " " << rhs.y << endl;
		return out;
	}

};

int operator*(const Point& lhs, const Point& rhs) {
	return lhs.x * rhs.y - rhs.x * lhs.y;
}

struct LessByAngle {
	explicit LessByAngle(const Point& center) : center(center) {
	}

	bool operator() (const Point& lhs, const Point& rhs) const {
		if (lhs == rhs) {
			return false;
		}
		if (lhs == center) {
			return true;
		}
		Point x = lhs;
		x -= center;
		Point y = rhs;
		y -= center;
		if (upper(x) != upper(y)) {
			return upper(y);
		}
		return x * y > 0;
	}
private:
	bool upper(const Point& point) const {
		return point.y > 0 || (point.y == 0 && point.x > 0);
	}

	const Point center;

};

bool eq(LessByAngle& cmp, const Point& lhs, const Point& rhs) {
	return !cmp(lhs, rhs) && !cmp(rhs, lhs);
}

class BearBall {
public:

    /// caide keep
    int countThrows(vector<int> x, vector<int> y) {
        int result = 0;
		const int n = x.size();
		vector<Point> a;
		for (int i = 0; i < n; ++i) {
			a.emplace_back(x[i], y[i]);
		}
		auto b = a;
		for (int i = 0; i < n; ++i) {
			LessByAngle cmp(b[i]);
			sort(a, cmp);
			for (int j = 1, cur_ind = 1; j < n; j = cur_ind) {
				while (cur_ind < n && eq(cmp, a[j], a[cur_ind])) {
					++cur_ind;
				}
				if (j == 1 && cur_ind == n) {
					result += n * (n - 1) / 2;
					continue;
				}
				for (int k = j, cnt = 0; k < cur_ind; ++k) {
					if (a[k] == b[i]) {
						continue;
					}
					++cnt;
					if (cnt == 1) {
						++result;
					}
					else {
						result += 2;
					}
				}
			}
		}
        return result;
    }
};


int solve(vector<int> x, vector<int> y, int) {
    BearBall sol;
    return sol.countThrows(x, y);
}

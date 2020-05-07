#pragma comment(linker, "/STACK:66777216")
#pragma warning(disable : 4996)

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#pragma hdrstop

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#ifdef _MSC_VER

#endif

template<typename T, size_t N>
struct MakeVector {
	
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#include <iterator>

template<typename R, typename Comp>
void sort(R& range, Comp comp) {
	std::sort(range.begin(), range.end(), comp);
}

using namespace std;

class Point {
public:
	int x, y;

	Point(int x, int y) : x(x), y(y) {}

	Point& operator-=(const Point& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	bool operator ==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
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


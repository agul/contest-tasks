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

static constexpr long long LINF = 0x3f3f3f3f3f3f3f3fLL;

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

template<typename T>
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

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

#define ll long long

namespace std {

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

}

#include <iterator>

template<typename T>
class IntegerIterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T> {
public:
	using value_type = T;

	constexpr explicit IntegerIterator(const value_type value) : value_(value) {}

	IntegerIterator& operator++() {
		++value_;
		return *this;
	}

	constexpr value_type operator*() const {
		return value_;
	}

	constexpr bool operator ==(const IntegerIterator rhs) const {
		return value_ == rhs.value_;
	}

	constexpr bool operator !=(const IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	value_type value_;

};

template<typename T>
class IntegerRange {
public:
	using const_iterator = IntegerIterator<T>;

	constexpr IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	constexpr const_iterator begin() const {
		return const_iterator(begin_);
	}

	constexpr const_iterator end() const {
		return const_iterator(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
constexpr IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

template<typename R, typename Comp>
void sort(R& range, Comp comp) {
	std::sort(range.begin(), range.end(), comp);
}

class Decimal {
public:
	/// caide keep
	using T = long double;

	/// caide keep
	constexpr Decimal() : Decimal(0) {}
	constexpr Decimal(const T value) : value_(value) {}

private:
	T value_;

};

template<typename T, typename SquareT = T, typename DecimalT = Decimal>
class Coord2D {
public:
	/// caide keep
	using value_type = T; 
	/// caide keep
	using square_type = SquareT; 
	/// caide keep
	using decimal_type = DecimalT; 
	/// caide keep
	using decimal_coord_type = Coord2D<decimal_type, decimal_type, decimal_type>; 

	/// caide keep
	constexpr Coord2D() : Coord2D(0, 0) {}
	constexpr Coord2D(const value_type x, const value_type y) : x(x), y(y) {}

	Coord2D& operator +=(const Coord2D& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	/// caide keep
	template<typename C>
	C as() const {
		return{ static_cast<typename C::value_type>(x), static_cast<typename C::value_type>(y) };
	}

	friend std::istream& operator >> (std::istream& in, Coord2D& rhs) {
		in >> rhs.x >> rhs.y;
		return in;
	}

	value_type x;
	value_type y;

protected:
	
};

template<typename T, typename SquareT = T, typename DecimalT = Decimal>
class Coord3D {
public:
	/// caide keep
	using value_type = T;
	/// caide keep
	using square_type = SquareT;
	/// caide keep
	using decimal_type = DecimalT;
	/// caide keep
	using decimal_coord_type = Coord3D<decimal_type, decimal_type, decimal_type>;

	/// caide keep
	constexpr Coord3D() : Coord3D(0, 0, 0) {}
	
	/// caide keep
	template<typename C>
	C as() const {
		return{ static_cast<typename C::value_type>(x), static_cast<typename C::value_type>(y), static_cast<typename C::value_type>(z) };
	}

	value_type x;
	value_type y;
	value_type z;

protected:
	
};

template<typename Coord>
struct is_2d
{
	/// caide keep
	static constexpr bool value = std::is_same<Coord, Coord2D<typename Coord::value_type, typename Coord::square_type, typename Coord::decimal_type>>::value;
};

template<typename Coord>
struct is_3d
{
	/// caide keep
	static constexpr bool value = std::is_same<Coord, Coord3D<typename Coord::value_type, typename Coord::square_type, typename Coord::decimal_type>>::value;
};

template<typename Coord>
class Vector;

template<typename Coord>
class Point : public Coord {
public:
	/// caide keep
	using vector_type = Vector<Coord>;
	/// caide keep
	using value_type = typename Coord::value_type;
	/// caide keep
	using square_type = typename Coord::square_type;
	/// caide keep
	using decimal_type = typename Coord::decimal_type;
	/// caide keep
	using coordinates_type = Coord;

	/// caide keep
	using decimal_point_type = Point<typename Coord::decimal_coord_type>;
	/// caide keep
	using decimal_vector_type = typename vector_type::decimal_vector_type;

	/// caide keep
	constexpr Point() : Coord() {}

	/// caide keep
	template<typename C = Coord, typename std::enable_if<is_2d<C>::value>::type* = nullptr>
	constexpr Point(const value_type x, const value_type y) : Coord(x, y) {}

	/// caide keep
	template<typename C = Coord, typename std::enable_if<is_3d<C>::value>::type* = nullptr>
	constexpr Point(const value_type x, const value_type y, const value_type z) : Coord(x, y, z) {}

	Point& operator +=(const Point& rhs) {
		Coord::operator +=(rhs);
		return *this;
	}

	/// caide keep
	template<typename P>
	constexpr P as() const {
		return P(Coord::template as<typename P::coordinates_type>());
	}
};

template<typename Coord>
class Vector : public Coord {
public:
	/// caide keep
	using point_type = Point<Coord>;
	/// caide keep
	using value_type = typename Coord::value_type;
	/// caide keep
	using square_type = typename Coord::square_type;
	/// caide keep
	using decimal_type = typename Coord::decimal_type;
	/// caide keep
	using coordinates_type = Coord;
	
	/// caide keep
	using decimal_vector_type = Vector<typename Coord::decimal_coord_type>;

	/// caide keep
	constexpr Vector() : Coord() {}

	/// caide keep
	template<typename C = Coord, typename std::enable_if<is_2d<C>::value>::type* = nullptr>
	constexpr Vector(const value_type x, const value_type y) : Coord(x, y) {}

	/// caide keep
	template<typename C = Coord, typename std::enable_if<is_3d<C>::value>::type* = nullptr>
	constexpr Vector(const value_type x, const value_type y, const value_type z) : Coord(x, y, z) {}

	/// caide keep
	template<typename V>
	constexpr V as() const {
		return V(Coord::template as<typename V::coordinates_type>());
	}
};

template<typename T, typename SquareT = T, typename DecimalT = Decimal>
using Point2D = Point<Coord2D<T, SquareT, DecimalT>>;

template<typename Coord>
struct is_2d<Point<Coord>>
{
	/// caide keep
	static constexpr bool value = is_2d<Coord>::value;
};

template<typename Coord>
struct is_3d<Point<Coord>>
{
	/// caide keep
	static constexpr bool value = is_3d<Coord>::value;
};

template<typename Coord>
struct is_2d<Vector<Coord>>
{
	/// caide keep
	static constexpr bool value = is_2d<Coord>::value;
};

template<typename Coord>
struct is_3d<Vector<Coord>>
{
	/// caide keep
	static constexpr bool value = is_3d<Coord>::value;
};

using namespace std;

const int MAGIC = 10;

using Pt = Point2D<ll>;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<Pt> points(n);
	in >> points;
	Pt mass;
	for (const auto& it : points) {
		mass += it;
	}
	sort(points, [](const Pt& lhs, const Pt& rhs) {
		return std::make_pair(lhs.x, lhs.y) < std::make_pair(rhs.x, rhs.y);
	});
	auto pointsY = points;
	sort(pointsY, [](const Pt& lhs, const Pt& rhs) {
		return std::make_pair(lhs.y, lhs.x) < std::make_pair(rhs.y, rhs.x);
	});
	ll xx = mass.x / n;
	ll yy = mass.y / n;

	auto dist = [&](const Pt& lhs, const ll x, const ll y) {
		return abs(lhs.x - x) + abs(lhs.y - y);
	};

	auto passY = [&](const ll x, const ll y) {
		ll posY = y - n / 2;
		ll ans = 0;
		for (int i : range(n)) {
			ans += dist(pointsY[i], x, posY);
			++posY;
		}
		return ans;
	};

	auto passX = [&](const ll x, const ll y) {
		ll posX = x - n / 2;
		ll ans = 0;
		for (int i : range(n)) {
			ans += dist(points[i], posX, y);
			++posX;
		}
		return ans;
	};

	ll ans = LINF;
	for (ll x = xx - MAGIC; x <= xx + MAGIC; ++x) {
		for (ll y = yy - MAGIC; y <= yy + MAGIC; ++y) {
			if (x == 1 && y == 2) {
				x = 1;
			}
			const ll curX = passX(x, y);
			const ll curY = passY(x, y);
			umin(ans, curX);
			umin(ans, curY);
		}
	}
	out << ans << endl;
}

#include <fstream>

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}


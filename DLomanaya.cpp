#include "base/header.hpp"

class DLomanaya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		using Point = pii;
		Point a, b, c;
		in >> a >> b >> c;

		auto is_on_the_same_line = [](const Point& lhs, const Point& rhs) {
			return lhs.X == rhs.X || lhs.Y == rhs.Y;
		};

		if (is_on_the_same_line(a, b) && is_on_the_same_line(b, c) && is_on_the_same_line(a, c)) {
			out << 1 << std::endl;
			return;
		}

		if (!is_on_the_same_line(a, b) && !is_on_the_same_line(b, c) && !is_on_the_same_line(a, c)) {
			out << 3 << std::endl;
			return;
		}

		auto count = [](const Point& a, const Point& b) {
			if (a.X != b.X && a.Y != b.Y) {
				return 2;
			}
			return 1;
		};

		auto monotonousX = [](const Point& a, const Point& b, const Point& c) {
			return (a.X <= b.X && b.X <= c.X) || (a.X >= b.X && b.X >= c.X);
		};

		auto monotonousY = [](const Point& a, const Point& b, const Point& c) {
			return (a.Y <= b.Y && b.Y <= c.Y) || (a.Y >= b.Y && b.Y >= c.Y);
		};

		auto check = [&count, &monotonousX, &monotonousY](const Point& a, const Point& b, const Point& c) {
			if (monotonousX(a, b, c) && monotonousY(a, b, c)) {
				return 2;
			}
			return 3;
		};

		int ans = std::min({
			check(a, b, c),
			check(a, c, b),
			check(b, a, c),
			check(b, c, a),
			check(c, a, b),
			check(c, b, a)
		});
		out << ans << std::endl;
		return;

		if (is_on_the_same_line(a, b) || is_on_the_same_line(b, c) || is_on_the_same_line(a, c)) {
			out << 2 << std::endl;
			return;
		}

		out << 3 << std::endl;
	}


	DLomanaya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};

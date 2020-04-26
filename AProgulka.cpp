#include "../algolib/cpplib/base/header.hpp"

class AProgulka {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int a, b, c, d, x, y, x1, y1, x2, y2;
			in >> a >> b >> c >> d >> x >> y >> x1 >> y1 >> x2 >> y2;
			bool ok = true;
			ok &= (x - a + b) >= x1;
			ok &= (x + b - a) <= x2;
			ok &= (y - c + d) >= y1;
			ok &= (y + d - c) <= y2;

			ok &= (x >= x1 && x <= x2);
			ok &= (y >= y1 && y <= y2);

			if (b > 0) {
				ok &= (x1 == x && x2 > x) || x1 < x;
			}
			if (a > 0) {
				ok &= (x2 == x && x1 < x) || x2 > x;
			}
			if (d > 0) {
				ok &= (y1 == y && y2 > y) || y1 < y;
			}
			if (c > 0) {
				ok &= (y2 == y && y1 < y) || y2 > y;
			}



			out << (ok ? "Yes" : "No") << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};

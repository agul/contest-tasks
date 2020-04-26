#include "base/header.hpp"

class APoluchiDvaNulya {
public:
	void solve(std::istream& in, std::ostream& out) {
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			ll n, a, b, x, y;
			in >> x >> y >> a >> b;
			if (x > y) {
				std::swap(x, y);
			}
			ll ans = std::min({
					(x + y) * a,
					(y - x) * a + x * b,
					(y - x) * a + y * b
			});
			out << ans << std::endl;
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

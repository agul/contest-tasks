#include "base/header.hpp"

class ANastyaIRis {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			ll n, a, b, c, d;
			in >> n >> a >> b >> c >> d;
			ll x1 = (a - b) * n;
			ll y1 = (a + b) * n;
			ll x2 = (c - d);
			ll y2 = (c + d);
			bool ok = (x1 <= y2 && y1 >= x2);
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

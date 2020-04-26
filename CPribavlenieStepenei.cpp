#include "../algolib/cpplib/base/header.hpp"

class CPribavlenieStepenei {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			int mx = a.front();
			int ans = 0;
			for (int i : range(1, n)) {
				const int diff = std::max(0, mx - a[i]);
				const int bits = clz(diff);
				const int cur_time = (diff == 0 ? 0 : 32 - bits);

				// out << a[i] << " " << mx << " " << diff << " " << " " << bits << " " << cur_time << std::endl;
				umax(ans, cur_time);
				umax(mx, a[i]);
			}
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

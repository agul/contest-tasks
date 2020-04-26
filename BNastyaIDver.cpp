#include "base/header.hpp"

class BNastyaIDver {
public:
	void solve(std::istream& in, std::ostream& out) {
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n, k;
			in >> n >> k;
			auto a = make_vector<int>(n, 0);
			in >> a;
			std::vector<bool> b(n, false);
			for (int i : range(1, n - 1)) {
				b[i] = (a[i] > a[i - 1] && a[i] > a[i + 1]);
			}
			int cur = 0;
			for (int i : range(1, k - 1)) {
				cur += (b[i] ? 1 : 0);
			}
			int ans = cur;
			int best = 0;
			for (int i : range(k - 1, n)) {
				cur += (b[i] ? 1 : 0);
				cur -= (b[i - k + 2] ? 1 : 0);
				if (umax(ans, cur)) {
					best = i - k + 2;
				}
			}
			out << ans + 1 << " " << best + 1 << std::endl;
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

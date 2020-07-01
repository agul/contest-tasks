#include "base/header.hpp"

class AXXXXX {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, x;
		in >> n >> x;
		std::vector<int> a(n);
		in >> a;

		const int sum = std::accumulate(all(a), 0);
		int cur_sum = 0;
		int ans = -1;
		for (int i : range(n)) {
			int suf_sum = sum - cur_sum;
			if (cur_sum % x != 0) {
				umax(ans, i);
			}
			if (suf_sum % x != 0) {
				umax(ans, n - i);
			}
			cur_sum += a[i];
			suf_sum -= a[i];
			if (cur_sum % x != 0) {
				umax(ans, i + 1);
			}
			if (suf_sum % x != 0) {
				umax(ans, n - i - 1);
			}
			debug(i, ans, suf_sum);
		}

		out << ans << std::endl;
	}


	AXXXXX() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

#include "base/header.hpp"

class BYunieSledopiti {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		std::vector<int> cnt(n + 1, 0);
		for (int x : a) {
			cnt[x] += 1;
		}

		int ans = 0;
		int rem = 0;
		for (int i : range(1, n + 1)) {
			int cur_cnt = cnt[i] + rem;
			ans += cur_cnt / i;
			rem = cur_cnt % i;
		}
		out << ans << std::endl;
	}


	BYunieSledopiti() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

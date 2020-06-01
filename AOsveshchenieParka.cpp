#include "base/header.hpp"

class AOsveshchenieParka {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;

		auto calc = [](const int n, const int m) {
			int ans = ((n - 1) / 2 + 1) * m;
			int left = n * m - (n / 2) * 2 * m;
			umin(ans, (n / 2) * m + (left - 1) / 2 + 1);
			return ans;
		};

		int ans = std::min(calc(n, m), calc(m, n));
		out << ans << std::endl;
	}


	AOsveshchenieParka() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

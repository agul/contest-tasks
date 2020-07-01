#include "base/header.hpp"

class CPlyusiIMinusi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;

		const int n = s.length();
		std::vector<int> a;
		a.reserve(s.length());
		int cur = 0;
		for (char ch : s) {
			if (ch == '+') {
				++cur;
			} else {
				--cur;
			}
			a.emplace_back(cur);
		}
		ll ans = 0;
		ll min = 0;
		for (int i : range(n)) {
			if (a[i] < min) {
				const ll diff = min - a[i];
				ans += diff * (i + 1);
				min = a[i];
			}
		}
		out << ans + n << std::endl;

	}


	CPlyusiIMinusi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

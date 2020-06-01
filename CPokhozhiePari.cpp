#include "base/header.hpp"

class CPokhozhiePari {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;
		int cnt_odd = 0;
		int cnt_even = 0;
		std::set<int> nums(all(a));
		for (int x : a) {
			if (x & 1) {
				++cnt_odd;
			} else {
				++cnt_even;
			}
		}
		if ((cnt_odd & 1) && (cnt_even & 1)) {
			for (int x : a) {
				if (nums.count(x - 1) > 0 || nums.count(x + 1) > 0) {
					out << "YES" << std::endl;
					return;
				}
			}
		}
		if (cnt_odd % 2 == 0 && cnt_even % 2 == 0) {
			out << "YES" << std::endl;
			return;
		}
		out << "NO" << std::endl;
	}


	CPokhozhiePari() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

#include "base/header.hpp"

class BTroichnayaStroka {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;
		std::vector<int> last(3, -1);
		int ans = 0;
		for (int i : range(s.size())) {
			const int x = s[i] - '1';
			last[x] = i;
			auto min = *min_element(last);
			if (min == -1) {
				continue;
			}
			int cur_value = i - min + 1;
			if (ans == 0 || ans > cur_value) {
				ans = cur_value;
			}
		}
		out << ans << std::endl;
	}


	BTroichnayaStroka() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

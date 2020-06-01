#include "base/header.hpp"

class BNovayaTeatralnayaPloshchad {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, m, x, y;
		in >> n >> m >> x >> y;
		std::vector<std::string> a(n);
		in >> a;
		int ans = 0;
		umin(y, x * 2);
		for (int i : range(n)) {
			int cnt = 0;
			for (int j : range(m)) {
				if (a[i][j] == '*') {
					ans += x * cnt;
					cnt = 0;
				} else {
					++cnt;
					if (cnt == 2) {
						ans += y;
						cnt = 0;
					}
				}
			}
			ans += x * cnt;
		}
		out << ans << std::endl;
	}


	BNovayaTeatralnayaPloshchad() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

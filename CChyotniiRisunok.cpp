#include "base/header.hpp"

class CChyotniiRisunok {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		std::vector<pii> ans;

		ans.emplace_back(-1, 1);

		for (int i : range(n)) {
			const int pos = i * 2;
			for (int x : range(2)) {
				for (int y : range(3)) {
					if (x == 0 || y == 1) {
						ans.emplace_back(pos + x, y);
					}
				}
			}
		}

		for (int i : range(0, n - 1)) {
			const int pos = i * 2;
			if (i % 2 == 0) {
				ans.emplace_back(pos, 3);
				ans.emplace_back(pos + 1, 3);
				ans.emplace_back(pos + 2, 3);
			} else {
				ans.emplace_back(pos, -1);
				ans.emplace_back(pos + 1, -1);
				ans.emplace_back(pos + 2, -1);
			}
		}

		ans.emplace_back(-1, 0);

		if (n % 2 == 0) {
			ans.emplace_back(n * 2 - 1, 0);
		} else {
			ans.emplace_back(n * 2 - 1, 2);
		}



		out << ans.size() << std::endl;
		for (const auto& pt : ans) {
			out << pt.first << " " << pt.second << std::endl;
		}
	}


	CChyotniiRisunok() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

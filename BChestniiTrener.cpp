#include "base/header.hpp"

class BChestniiTrener {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		int ans = INF;
		for (int lim : range(1010)) {
			int cnta = 0;
			int cntb = 0;
			int maxa = 0;
			int minb = INF;
			int cntlim = 0;
			for (int x : a) {
				if (x <= lim) {
					if (x == lim) {
						++cntlim;
					}
					++cnta;
					umax(maxa, x);
				} else {
					++cntb;
					umin(minb, x);
				}
				if (cntlim > 1) {
					ans = 0;
					break;
				}
				if (cnta == 0 || cntb == 0) {
					continue;
				}
				umin(ans, std::abs(maxa - minb));
			}
		}
		out << ans << std::endl;
	}


	BChestniiTrener() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

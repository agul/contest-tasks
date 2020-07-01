#include "base/header.hpp"

class CPalindromniePuti {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		auto cnt = make_vector<int>(n + m, 2, 0);
		for (int i : range(n)) {
			for (int j : range(m)) {
				int x;
				in >> x;
				cnt[i + j][x]++;
			}
		}
		int ans = 0;
		const int total_distance = (n - 1) + (m - 1);
		for (int i : inclusiveRange(total_distance / 2)) {
			debug(i);
			const int opposite = total_distance - i;
			if (i == opposite) {
				break;
			}
			ans += std::min(cnt[i][0] + cnt[opposite][0], cnt[i][1] + cnt[opposite][1]);
		}
		out << ans << std::endl;
	}


	CPalindromniePuti() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

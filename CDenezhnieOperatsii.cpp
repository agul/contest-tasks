#include "base/header.hpp"

class CDenezhnieOperatsii {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		ll pref = 0;
		int max_count = 0;
		SafeUnorderedMap<ll, int> cnt;
		for (int x : a) {
			pref += x;
			cnt[pref] += 1;
			umax(max_count, cnt[pref]);
		}
		out << n - max_count << std::endl;
	}


	CDenezhnieOperatsii() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};

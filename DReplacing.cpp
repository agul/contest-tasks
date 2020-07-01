#include "base/header.hpp"

class DReplacing {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<ll> a(n);
		in >> a;

		SafeUnorderedMap<ll, int> cnt;
		for (int x : a) {
			cnt[x] += 1;
		}

		int q;
		in >> q;

		ll sum = std::accumulate(all(a), 0LL);


		for (int i : range(q)) {
			ll x, y;
			in >> x >> y;
			auto it = cnt.find(x);
			if (it != cnt.cend()) {
				const int cur_cnt = it->second;
				sum -= x * cur_cnt;
				cnt.erase(x);
				cnt[y] += cur_cnt;
				sum += y * cur_cnt;
			}
			out << sum << std::endl;
		}
	}


	DReplacing() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

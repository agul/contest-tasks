#include "base/header.hpp"

class CVrazhdebniePari {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<int> a(n);
		in >> a;

		std::vector<int> pos(n);
		for (int i : range(n)) {
			--a[i];
			pos[a[i]] = i;
		}

		std::multiset<int> bad_pair_ends;
		std::multiset<pii> bad_pairs;
		for (int i : range(m)) {
			int x, y;
			in >> x >> y;
			--x, --y;

			const int left = std::min(pos[x], pos[y]);
			const int right = std::max(pos[x], pos[y]);
			bad_pair_ends.emplace(right);
			bad_pairs.emplace(left, right);
		}
		bad_pairs.emplace(n, n);
		bad_pair_ends.emplace(n);

		ll ans = 0;
		for (int i : range(n)) {
			while (bad_pairs.begin()->first < i) {
				const auto it = bad_pairs.begin();
				bad_pair_ends.erase(bad_pair_ends.find(it->second));
				bad_pairs.erase(it);
			}
			const int first = *bad_pair_ends.begin();
			ans += first - i;
		}

		out << ans << std::endl;
	}


	CVrazhdebniePari() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

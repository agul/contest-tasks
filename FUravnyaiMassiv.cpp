#include "base/header.hpp"

class FUravnyaiMassiv {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        SafeUnorderedMap<int, int> cnt;
        for (int x : a) {
            cnt[x] += 1;
        }

        std::vector<int> counts;
        for (const auto& it : cnt) {
            counts.emplace_back(it.second);
        }
        sort(counts);

        const int m = counts.size();

        ll ans = LINF;
        int index = 0;
        for (ll c : range(n + 1)) {
            while (index < m && counts[index] < c) {
                ++index;
            }

            umin(ans, n - c * (m - index));
        }
        out << ans << std::endl;
	}


	FUravnyaiMassiv() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

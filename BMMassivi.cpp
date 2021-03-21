#include "base/header.hpp"

class BMMassivi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<int> a(n);
        in >> a;

        std::map<int, int> cnt;
        for (int x : a) {
            ++cnt[x % m];
        }

        auto get = [&cnt](const int rem) {
            const auto it = cnt.find(rem);
            if (it == cnt.cend()) {
                return 0;
            }
            return it->second;
        };

        int ans = 0;
        if (cnt.count(0)) {
            ++ans;
            cnt.erase(0);
        }

        while (!cnt.empty()) {
            auto it = cnt.begin();
            const int cur_rem = it->first;
            const int next_rem = m - cur_rem;

            int cur_count = it->second;
            int next_count = get(next_rem);

            cnt.erase(cur_rem);
            cnt.erase(next_rem);

            const int min = std::min(cur_count, next_count);
            cur_count -= min;
            next_count -= min;

            if (cur_count > 0) {
                --cur_count;
            }
            if (next_count > 0) {
                --next_count;
            }
            ans += 1 + cur_count + next_count;
        }
        out << ans << std::endl;
	}


	BMMassivi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

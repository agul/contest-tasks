#include "base/header.hpp"

class APoeduDomoi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	const int MAXN = 5555555;

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<pii> a;
        for (int i : range(n)) {
            int x;
            in >> x;
            a.emplace_back(x, i);
        }
        sort(a);

        auto diffs = make_vector<pii>(MAXN, 0, pii{});
        for (int i : range(1, n)) {
            diffs[a[i].first - a[i - 1].first].emplace_back(a[i - 1].second, a[i].second);
        }

        auto result = [&out](const pii& a, const pii& b) {
            out << "YES" << std::endl;
            out << a.first + 1 << " " << b.second + 1 << " " << b.first + 1 << " " << a.second + 1 << std::endl;
        };

        for (const auto& diff : diffs) {
            if (diff.size() < 2 || diff.front().second == diff.back().first) {
                continue;
            }
            result(diff.front(), diff.back());
            return;
        }

        if (n <= 5000) {
            std::vector<pii> min(MAXN, pii{INF, INF});
            std::vector<pii> max(MAXN, pii{-1, -1});
            for (int i : range(n)) {
                for (int j : range(i + 1, n)) {
                    const int sum = a[i].first + a[j].first;
                    umin(min[sum], pii{i, j});
                    umax(max[sum], pii{i, j});
                }
            }
            for (int i : range(MAXN)) {
                if (min[i].first != INF && min[i].second != max[i].first && min[i].second != max[i].second && min[i].first != max[i].first) {
                    result(pii{min[i].first, max[i].second}, pii{max[i].first, min[i].second});
                    return;
                }
            }
        }

        out << "NO" << std::endl;
	}


	APoeduDomoi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

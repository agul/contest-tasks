#include "base/header.hpp"

class BPeredEkzamenom {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<int> a(n);
        in >> a;

        const int t = n / k;
        int q;
        in >> q;
        std::vector<bool> used(n, false);
        int min = INF;
        int max = -INF;
        for (int i : range(q)) {
            int sum = 0;
            for (int j : range(t)) {
                int x;
                in >> x;
                --x;

                used[x] = true;
                sum += a[x];
            }
            umin(min, sum);
            umax(max, sum);
        }

        std::vector<int> remaining;
        for (int i : range(n)) {
            if (!used[i]) {
                remaining.emplace_back(a[i]);
            }
        }
        sort(remaining);
        if (remaining.size() >= t && n - n / k * k < remaining.size()) {
            int min_sum = 0;
            int max_sum = 0;
            for (int i : range(t)) {
                min_sum += remaining[i];
                max_sum += remaining[remaining.size() - 1 - i];
            }
            umin(min, min_sum);
            umax(max, max_sum);
        }
        out << static_cast<double>(min) / t << " " << static_cast<double>(max) / t << std::endl;
	}


	BPeredEkzamenom() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

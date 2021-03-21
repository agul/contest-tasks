#include "base/header.hpp"

class AYaroslavIPosledovatelnost {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int k;
        in >> k;
        int n = 2 * k - 1;
        std::vector<int> positive;
        std::vector<int> negative;
        for (int i : range(n)) {
            int x;
            in >> x;
            if (x < 0) {
                negative.emplace_back(-x);
            } else {
                positive.emplace_back(x);
            }
        }
        sort(negative);
        while (negative.size() >= k) {
            for (int i : range(k)) {
                positive.emplace_back(negative.back());
                negative.pop_back();
            }
        }
        while (negative.size() > 1) {
            positive.emplace_back(negative.back());
            negative.pop_back();

            positive.emplace_back(negative.back());
            negative.pop_back();
        }
        sort(positive);
        if (!negative.empty() && negative.back() > positive.front()) {
            std::swap(negative.back(), positive.front());
        }

        if (negative.size() == 1 && k % 2 == 1) {
            positive.emplace_back(negative.back());
            negative.pop_back();
        }

        const int ans = std::accumulate(all(positive), 0) - std::accumulate(all(negative), 0);
        out << ans << std::endl;
	}


	AYaroslavIPosledovatelnost() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

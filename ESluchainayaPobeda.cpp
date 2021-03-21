#include "base/header.hpp"

class ESluchainayaPobeda {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<pii> a;
        ll total = 0;
        for (int i : range(n)) {
            int x;
            in >> x;
            a.emplace_back(x, i);
            total += x;
        }
        sort(a, std::greater<>());
        std::vector<int> winners;
        int prev = -1;
        for (int i : range(n)) {
            if (total >= prev) {
                winners.emplace_back(a[i].second);
            } else {
                break;
            }
            prev = a[i].first;
            total -= a[i].first;
        }

        sort(winners);
        out << winners.size() << std::endl;
        for (int x : winners) {
            out << x + 1 << " ";
        }
        out << std::endl;
	}


	ESluchainayaPobeda() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

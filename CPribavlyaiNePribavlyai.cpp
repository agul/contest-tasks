#include "base/header.hpp"

class CPribavlyaiNePribavlyai {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        ll k;
        in >> n >> k;
        std::vector<ll> a(n);
        in >> a;
        sort(a);

        int index = 0;
        ll last = a.front();
        ll diff = 0;
        int max = 1;
        ll best = a.front();
        for (int i : range(n)) {
            diff += (a[i] - last) * (i - index);
            while (diff > k) {
                diff -= a[i] - a[index];
                ++index;
            }
            if (umax(max, i - index + 1)) {
                best = a[i];
            }
            last = a[i];
        }
        out << max << " " << best << std::endl;
	}


	CPribavlyaiNePribavlyai() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

#include "base/header.hpp"

class BNovayaKoloniya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<ll> a(n);
        in >> a;

        const int maxn = std::min(k, 20000);
        for (int stone : range(maxn)) {
            int last = n - 1;
            for (int i : range(n - 1)) {
                if (a[i] < a[i + 1]) {
                    last = i;
                    break;
                }
            }
            if (last == n - 1) {
                break;
            }
            a[last] += 1;
            if (stone == k - 1) {
                out << last + 1 << std::endl;
                return;
            }
        }
        out << -1 << std::endl;
	}


	BNovayaKoloniya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

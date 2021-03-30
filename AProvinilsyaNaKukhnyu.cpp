#include "base/header.hpp"
#include "maths/decimal.hpp"

class AProvinilsyaNaKukhnyu {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, v;
        in >> n >> v;
        std::vector<int> a(n), b(n);
        in >> a >> b;

        Decimal L = 0, R = 10000;
        Decimal ans = 0;
        for (int iter : range(100)) {
            const Decimal md = (L + R) / 2;
            bool ok = true;
            Decimal sum = 0;
            for (int i : range(n)) {
                if (md * a[i] > b[i]) {
                    ok = false;
                    break;
                }
                sum += md * a[i];
            }
            if (sum > v) {
                ok = false;
            }
            if (!ok) {
                R = md;
            } else {
                L = md;
                ans = sum;
            }
        }
        out << ans << std::endl;
	}


	AProvinilsyaNaKukhnyu() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

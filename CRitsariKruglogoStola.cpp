#include "base/header.hpp"
#include "maths/maths.hpp"

class CRitsariKruglogoStola {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        auto divs = divisors_vector(n);
        for (const int len : divs) {
            if (n / len < 3) {
                continue;
            }
            for (int start : range(len)) {
                bool ok = true;
                for (int i = start; i < n && ok; i += len) {
                    ok &= (a[i] == 1);
                }
                if (ok) {
                    out << "YES" << std::endl;
                    return;
                }
            }
        }
        out << "NO" << std::endl;
	}


	CRitsariKruglogoStola() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

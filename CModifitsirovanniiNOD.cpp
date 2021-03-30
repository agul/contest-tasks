#include "base/header.hpp"
#include "maths/maths.hpp"

class CModifitsirovanniiNOD {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int a, b, queries;
        in >> a >> b >> queries;
        const int g = gcd(a, b);
        auto divs = divisors_vector(g);
        sort(divs);
        debug(divs);

        for (int query : range(queries)) {
            int l, r;
            in >> l >> r;
            const auto it = upper_bound(divs, r);
            int ans = -1;
            if (it != divs.cbegin()) {
                auto prev = std::prev(it);
                if (*prev >= l) {
                    ans = *prev;
                }
            }
            out << ans << std::endl;
        }
	}


	CModifitsirovanniiNOD() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

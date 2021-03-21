#include "base/header.hpp"

class BOchenKrasivoeChislo {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<int> a(n);
        for (int last_digit : range(1, 10)) {
            a[0] = last_digit;
            int carry = 0;
            int last = last_digit;
            for (int i : range(1, n)) {
                const int res = last * k + carry;
                a[i] = res % 10;
                carry = res / 10;
                last = a[i];
            }
            reverse(a); debug(a); reverse(a); debug(carry);
            if (last * k + carry == last_digit && a.back() != 0) {
                reverse(a);
                for (int x : a) {
                    out << x;
                }
                out << std::endl;
                return;
            }
        }
        out << "Impossible" << std::endl;
	}


	BOchenKrasivoeChislo() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

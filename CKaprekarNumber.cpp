#include "base/header.hpp"
#include "maths/maths.hpp"

class CKaprekarNumber {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        ll n;
        int k;
        in >> n >> k;
        ll prev = -1;
        for (int i : range(k)) {
            auto d = digits(n);
            sort(d);

            ll a = 0;
            ll b = 0;
            for (int x : d) {
                a = a * 10 + x;
            }
            reverse(d);
            for (int x : d) {
                b = b * 10 + x;
            }
            debug(n, b, a, b - a);
            prev = n;
            n = b - a;
            if (n == prev) {
                break;
            }
        }
        out << n << std::endl;
	}


	CKaprekarNumber() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

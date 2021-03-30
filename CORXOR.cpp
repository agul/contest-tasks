#include "base/header.hpp"
#include "maths/bits.hpp"

class CORXOR {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        ll ans = LINF;
        for (int mask : range(1 << n)) {
            ll bit_xor = 0;
            ll bit_or = 0;
            for (int i : range(n)) {
                bit_or |= a[i];
                if (test_bit(mask, i)) {
                    bit_xor ^= bit_or;
                    bit_or = 0;
                }
            }
            bit_xor ^= bit_or;
            umin(ans, bit_xor);
        }
        out << ans << std::endl;
	}


	CORXOR() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

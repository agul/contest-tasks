#include "base/header.hpp"
#include "maths/mod_int.hpp"

class BProductsOfMinMax {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<int, 998244353>;

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<Int> a(n);
        in >> a;
        sort(a);

        Int ans = 0;
        Int cur = 0;
        Int last = 0;
        for (int i : range(n)) {
            cur *= 2;
            cur -= last;
            cur += a[i];
            ans += a[i] * cur;
            last = a[i];
        }
        out << ans << std::endl;
	}


	BProductsOfMinMax() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

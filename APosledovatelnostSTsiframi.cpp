#include "base/header.hpp"
#include "maths/maths.hpp"

class APosledovatelnostSTsiframi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll n, k;
		in >> n >> k;
		if (k == 1) {
			out << n << std::endl;
			return;
		}
		ll prev = n;
		--k;
		for (int i : range(std::min(1000LL, k))) {
			auto a = digits(n);
			n += *min_element(a) * *max_element(a);
			if (n == prev || i == k - 1) {
				out << n << std::endl;
				return;
			}
			prev = n;
		}
		debug(n, k);
		assert(false);
	}


	APosledovatelnostSTsiframi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const ll KMaxValue = 1000000000000000LL;

		test << 1000 << std::endl;
		for (int i : range(1000)) {
			test << Random::get(1LL, KMaxValue) << " 10000000000000000" << std::endl;
		}
	}

};

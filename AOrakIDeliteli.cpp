#include "base/header.hpp"
#include "maths/maths.hpp"

class AOrakIDeliteli {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll n, k;
		in >> n >> k;
		auto divs = divisors_vector(n);
		sort(divs);
		ll fn = divs[1];
		n += fn;
		umin(fn, 2LL);
		--k;
		n += k * fn;
		out << n << std::endl;
	}


	AOrakIDeliteli() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

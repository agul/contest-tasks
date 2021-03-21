#include "base/header.hpp"
#include "maths/mod_int.hpp"

class ENerazreshimost {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<ll>;

	std::vector<ll> ans = {1, 2, 4, 6, 12, 16, 18, 30, 60, 88, 106, 126, 520, 606, 1278, 2202, 2280, 3216, 4252, 4422, 9688, 9940, 11212, 19936, 21700, 23208, 44496, 86242, 110502, 132048, 216090, 756838, 859432, 1257786, 1398268, 2976220, 3021376, 6972592, 13466916, 20996010, 24036582, 25964950, 30402456};

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        const Int res = binpow(Int{2}, ans[n - 1]) - Int{1};
        out << res << std::endl;
	}


	ENerazreshimost() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

#include "base/header.hpp"
#include "maths/bits.hpp"

class DProgulkaPoMatritse {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		if (n == 0) {
			out << "1 1\n1" << std::endl;
			return;
		}

		const int start = (bit_ceil(n + 1) << 1) - 1;
		const int last = start >> 1;
		out << "2 3" << std::endl;
		out << start << " " << last << " " << last - n << std::endl;
		out << (last + 1) << " " << start << " " << last << std::endl;
	}


	DProgulkaPoMatritse() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int x;
		in >> x;

		int n, m;
		out >> n >> m;
		auto a = make_vector<int>(n, m, 0);
		out >> a;

		if (n != 2 || m != 3) {
			return x == 0;
		}

		const int mx = a[0][0] & a[0][1] & a[0][2] & a[1][2];
		const int ans = a[0][0] & a[0][1] & a[1][1] & a[1][2];

		if (ans - mx != x) {
			debug(x, ans, mx);
			return false;
		}

		return true;
	}



	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		static int test_id = 0;
		++test_id;
		test << test_id << std::endl;
	}

};

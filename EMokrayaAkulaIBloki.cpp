#include "base/header.hpp"
#include "maths/mod_int.hpp"
#include "maths/matrix.hpp"

class EMokrayaAkulaIBloki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<ll>;

	void solve(std::istream& in, std::ostream& out) {
		int n, b, k, x;
		in >> n >> b >> k >> x;
		std::vector<int> a(n);
		in >> a;

		std::vector<int> cnt(x);
		for (int val : a) {
			++cnt[val % x];
		}

		Matrix<Int> mat(x, x);
		for (int mod : range(x)) {
			for (int i : range(x)) {
				const int cur_index = (mod + x - i * 10 % x) % x;
				mat[i][mod] = cnt[cur_index];
			}
		}

		auto pow = mat.binpow(b);
		out << pow[0][k] << std::endl;
	}


	EMokrayaAkulaIBloki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

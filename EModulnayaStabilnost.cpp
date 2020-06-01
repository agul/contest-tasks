#include "base/header.hpp"
#include "maths/permutation.hpp"
#include "maths/mod_int.hpp"
#include "maths/maths.hpp"

class EModulnayaStabilnost {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	const int kMaxn = 12;
	std::vector<int> a;

	int dfs(const int pos, const int len, const int maxn) {
		if (pos == len) {
			for (int i : inclusiveRange(maxn)) {
				bool all_equal = true;
				int value = -1;
				Permutation<int> p(len);
				do {
					int cur_value = i;
					for (int x : p) {
						cur_value %= a[x];
					}
					if (value == -1) {
						value = cur_value;
					}
					if (cur_value != value) {
						all_equal = false;
						break;
					}
				} while (p.next());
				if (!all_equal) {
					return 0;
				}
			}
			debug(a);
			return 1;
		}
		int result = 0;
		const int min_value = (pos > 0 ? a[pos - 1] + 1 : 1);
		for (int i = min_value; i <= maxn; ++i) {
			a[pos] = i;
			result += dfs(pos + 1, len, maxn);
		}
		return result;
	}

	using Int = ModInt<int, 998244353>;
	std::vector<Int> factorials;

	void solve(std::istream& in, std::ostream& out) {
//		a.resize(kMaxn);
//		out << dfs(0, 4, 12) << std::endl;
		int n, k;
		in >> n >> k;

		auto binom = [&](const int n, const int k) {
			if (n < k) {
				return Int{0};
			}
			return factorials[n] * factorials[k].inverse() * factorials[n - k].inverse();
		};


		Int ans = 0;
		for (int i : inclusiveRange(1, n)) {
			ans += binom(n / i - 1, k - 1);
		}
		out << ans << std::endl;
	}


	EModulnayaStabilnost() {
		factorials = calc_factorial<Int>(555555);
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

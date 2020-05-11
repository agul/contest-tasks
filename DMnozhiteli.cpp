#include "base/header.hpp"
#include "maths/mod_int.hpp"

class DMnozhiteli {
public:
	using Int = ModInt<int, 1000000007>;

	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		sort(a);

		Int N = 1;
		SafeUnorderedMap<int, int> cnt;
		for (int x : a) {
			N *= x;
			cnt[x] += 1;
		}

		Int ans = N;
		bool any_odd = false;
		for (const auto& it : cnt) {
			size_t degree = it.second + 1;
			if (degree % 2 == 0 && !any_odd) {
				degree /= 2;
				any_odd = true;
			}
			ans = binpow(ans, degree);
		}
		if (!any_odd) {
			Int sqrt = 1;
			for (const auto& it : cnt) {
				sqrt *= binpow(Int(it.first), it.second / 2);
			}
			ans = N;
			bool first = true;
			for (const auto& it : cnt) {
				size_t degree = it.second + 1;
				if (first) {
					ans = binpow(ans, degree / 2) * sqrt;
					first = false;
					continue;
				}
				ans = binpow(ans, degree);
			}
		}
		out << ans << std::endl;
	}


	DMnozhiteli() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};

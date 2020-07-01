#include "base/header.hpp"

class ALopatiIMechi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll a, b;
		in >> a >> b;
		if (a < b) {
			std::swap(a, b);
		}

		auto check = [a, b](const ll md) {
			if (md < 0 || md > b || md * 2 > a) {
				return 0LL;
			}
			ll aa = a - md * 2;
			ll bb = b - md;
			return md + std::min(aa, bb / 2);
		};

		ll L = 0;
		ll R = b + 1;
		while (R - L > 2) {
			int diff = (R - L) / 3;
			int m1 = L + diff;
			int m2 = R - diff;
			if (check(m1) > check(m2)) {
				R = m2;
			} else {
				L = m1;
			}
		}
		ll ans = 0;
		for (ll i : inclusiveRange(L - 10, R + 10)) {
			umax(ans, check(i));
		}
		out << ans << std::endl;

//		ll ans = std::min(a / 3, b / 3);
//		ll aa = a - ans * 3;
//		ll bb = b - ans * 3;
//		if (aa < bb) {
//			std::swap(aa, bb);
//		}
//		ans *= 2;
//		ans += std::min(aa / 2, bb);
//
//		umax(ans, std::min(a / 2, b));
//		umax(ans, std::min(a, b / 2));
//
//		out << ans << std::endl;
	}

	int solve_slow(int a, int b) {
		int ans = 0;
		if (a < b) {
			std::swap(a, b);
		}
		for (int i : inclusiveRange(b)) {
			if (i * 2 > a) {
				break;
			}
			int aa = a - i * 2;
			int bb = b - i;
			umax(ans, i + std::min(bb / 2, aa));
		}
		return ans;
	}


	ALopatiIMechi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;
		for (int i : range(testsCount)) {
			int a, b;
			in >> a >> b;
			const int jans = solve_slow(a, b);
			int pans;
			out >> pans;

			if (jans != pans) {
				debug(a, b, jans, pans);
				return false;
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 100000;
		test << 1 << std::endl;
		test << Random::get(1, kMaxn) << " " << Random::get(1, kMaxn) << std::endl;
	}

};

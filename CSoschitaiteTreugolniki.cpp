#include "base/header.hpp"

class CSoschitaiteTreugolniki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		ll A, B, C, D;
		in >> A >> B >> C >> D;
		ll ans = 0;

		auto sum_1_n = [](const ll n) {
			if (n < 0) {
				return 0LL;
			}
			return n * (n + 1) / 2;
		};

		ll prev = 0;
		for (ll y : inclusiveRange(B, C)) {
			const ll x = C - y + 1;
			debug(x, y);
			if (x > B) {
				continue;
			}

			ll cur_left = x;
			ll cur_right = C;



			if (x < A) {
				const ll x_a = A - x;
				const ll d_c = D - C;
				debug(x_a, d_c);

				if (x_a < d_c) {
					// ans += x_a * (B - A + 1);
					cur_left += x_a;
					cur_right += x_a;
				} else {
					ans += (B - A + 1) * (D - C + 1);
					continue;
				}
				debug(ans, cur_left, cur_right);
			}



			const ll dist_to_d = D - cur_right;
			const ll dist_to_c = cur_right - C;

			const ll dist_to_b = B - cur_left;
			if (dist_to_b <= dist_to_d) {
				const ll max_right = cur_right + dist_to_b;
				ans += sum_1_n(max_right - C + 1) - sum_1_n(cur_right - C);
			} else {
				ans += sum_1_n(D - C) - sum_1_n(cur_right - C);
				cur_left += dist_to_d;
				cur_right += dist_to_d;
				ans += (B - cur_left + 1) * (D - C + 1);
			}

			const ll cur_value = ans - prev;
			prev = ans;
			debug(y, cur_value);
		}
		out << ans << std::endl;

	}


	CSoschitaiteTreugolniki() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		ll A, B, C, D;
		in >> A >> B >> C >> D;
		ll jans = 0;
		for (ll x : inclusiveRange(A, B)) {
			for (ll y : inclusiveRange(B, C)) {
				const ll min_value = C;
				const ll max_value = std::min(D, x + y - 1);
				if (max_value < min_value) {
					continue;
				}
				// debug(x, y, min_value, max_value);
				jans += (max_value - min_value + 1);
			}
		}
		ll pans;
		out >> pans;
		if (jans != pans) {
			debug(jans, pans);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxValue = 1000;
		const int A = Random::get(1, kMaxValue);
		const int B = Random::get(A, kMaxValue);
		const int C = Random::get(B, kMaxValue);
		const int D = Random::get(C, kMaxValue);
		test << A << " " << B << " " << C << " " << D << std::endl;
	}

};

#include "base/header.hpp"
#include "maths/maths.hpp"


class EllysPalMul {
public:

	std::vector<ll> palindromes;

	ll reverse_num(ll x) {
		ll rev = 0;
		while (x > 0) {
			rev = rev * 10 + x % 10;
			x /= 10;
		}
		return rev;
	}

	int digits_count(ll x) {
		int ans = 0;
		while (x > 0) {
			++ans;
			x /= 10;
		}
		return ans;
	}

	ll make_palindrome(ll left, ll value) {
		while (value > 0) {
			left = left * 10 + value % 10;
			value /= 10;
		}
		return left;
	}

	int getMin(int X) {

		if (reverse_num(X) == X) {
			return 1;
		}

		std::vector<ll> pows(18);
		pows[0] = 1;
		for (int i = 1; i < 18; ++i) {
			pows[i] = pows[i - 1] * 10;
		}

		ll best = 0x3f3f3f3f;

		for (ll left = 1; left < 10000000; ++left) {
			const int pow = digits_count(left);

			const ll a_pal = make_palindrome(left, left);
			if (a_pal % X == 0) {
				best = std::min(best, a_pal / X);
			}

			const ll left_part = left * pows[pow + 1];
			for (int digit = 0; digit < 10; ++digit) {
				const ll b_pal = make_palindrome(left * 10 + digit, left);
				if (b_pal % X == 0) {
					best = std::min(best, b_pal / X);
					// debug(b_pal);
				}
			}

		}
		if (best > 1000000000) {
			return -1;
		}
		return best;
	}
};

class SRM785_easy {
public:

	void solve(std::istream& in, std::ostream& out) {
		int x;
		in >> x;
		EllysPalMul solution;
		out << solution.getMin(x) << std::endl;
	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};

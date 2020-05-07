#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/combination.hpp"

using namespace std;

int __;
const int MOD = 2520;
const int MAXN = 11111111;

ll dp[20][MOD][512][2];
std::vector<int> sup_masks[512];
std::vector<std::vector<int>> binoms;

std::vector<int> get_digits(const ll n) {
	std::vector<int> res;
	ll tmp = n;
	while (tmp > 0) {
		res.emplace_back(static_cast<int>(tmp % 10));
		tmp /= 10;
	}
	return res;
}

ll get_ans(const ll n, const int k) {
	if (n == 0) {
		return 0;
	}
	if (k == 0) {
		return n;
	}
	auto digits = get_digits(n);
	const int num_len = digits.size();


	reverse(digits);
	fill(dp, 0);
	dp[0][0][0][1] = 1;
	for (int pos : range(num_len)) {
		for (int rem : range(MOD)) {
			for (int mask : range(512)) {
				for (int prefix : range(2)) {
					const ll cur_val = dp[pos][rem][mask][prefix];
					if (cur_val == 0) {
						continue;
					}
					int finish = 10;
					if (prefix == 1) {
						finish = digits[pos] + 1;
					}
					for (int next_digit : range(finish)) {
						int new_rem = (rem * 10 + next_digit) % MOD;
						int new_mask = mask;
						if (next_digit != 0) {
							new_mask |= (1 << (next_digit - 1));
						}
						int new_prefix = 0;
						if (prefix && next_digit == digits[pos]) {
							new_prefix = 1;
						}
						dp[pos + 1][new_rem][new_mask][new_prefix] += cur_val;
					}
				}
			}
		}
	}

	std::vector<ll> total_cnt(11);
	for (int len : range(1, 10)) {
		Combination<int> comb(9, len);
		do {
			int mask = 0;
			int cur_lcm = 1;
			for (const auto& it : comb) {
				mask |= (1 << it);
				cur_lcm = lcm(cur_lcm, it + 1);
			}
			ll cur_val = 0;
			for (const auto& sup_mask : sup_masks[mask]) {
				for (int rem = 0; rem < MOD; rem += cur_lcm) {
					for (int prefix : range(2)) {
						cur_val += dp[num_len][rem][sup_mask][prefix];
					}
				}
			}
			total_cnt[len] += cur_val;
		} while (comb.next());
	}
	std::vector<ll> real_cnt(11);
	std::vector<ll> pref(11, 0);
	for (int i : inclusiveDownrange(9)) {
		real_cnt[i] = total_cnt[i];
		int used = 1;
		for (int j : range(i + 1, 10)) {
			int need = binoms[j][i] - used;
			real_cnt[i] -= real_cnt[j] * need;
			used += need;
		}
	}
	return real_cnt[k];
}

void solve(std::istream& in, std::ostream& out) {
	binomial_coefficients(10, &binoms);
	for (int mask : range(512)) {
		sup_masks[mask].clear();
	}
	for (int mask : range(512)) {
		for (int submask = mask; submask != 0; submask = (submask - 1) & mask) {
			sup_masks[submask].emplace_back(mask);
		}
	}
	in >> __;
	for (int _ : range(__)) {
		ll L, R;
		int k;
		in >> L >> R >> k;
		const ll ans = get_ans(R, k) - get_ans(L - 1, k);
		out << ans << endl;
	}
}

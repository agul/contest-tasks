#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void output(std::ostream& out, const std::vector<ll>& a) {
	for (const auto& it : a) {
		out << it << " ";
	}
	out << endl;
}

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	ll x;
	in >> n >> k >> x;
	vector<ll> a(n);
	in >> a;
	ll mx = x * k;

	int cnt_zeroes = std::count(all(a), 0);
	int cnt_negative = 0;
	ll max_negative = -LINF;
	ll min_positive = LINF;
	for (const auto& it : a) {
		if (it == 0) {
			continue;
		}
		if (it > 0) {
			umin(min_positive, it);
		}
		else {
			umax(max_negative, it);
			++cnt_negative;
		}
	}

	if (cnt_zeroes == 0 && cnt_negative % 2 == 0 && max_negative + mx <= 0 && min_positive - mx >= 0) {
		ll to_find = (abs(max_negative) < min_positive ? max_negative : min_positive);

		for (auto& it : a) {
			if (it == to_find) {
				if (it < 0) {
					it += mx;
				}
				else {
					it -= mx;
				}
				break;
			}
		}

		output(out, a);
		return;
	}

	if (cnt_negative % 2 == 0) {
		if (cnt_zeroes > 0) {
			if (k == 0) {
				output(out, a);
				return;
			}
			--k;
			for (auto& it : a) {
				if (it == 0) {
					it -= x;
					break;
				}
			}
		}
		else 
		if (abs(min_positive) < abs(max_negative)) {
			ll cur_cnt = min_positive / x;
			for (auto& it : a) {
				if (it == min_positive) {
					it %= x;
					if (k < cur_cnt) {
						output(out, a);
						return;
					}
					k -= cur_cnt;
					if (it >= 0) {
						if (k == 0) {
							output(out, a);
							return;
						}
						--k;
						it -= x;
					}
					break;
				}
			}
		}
		else {
			ll cur_cnt = abs(max_negative) / x;
			for (auto& it : a) {
				if (it == max_negative) {
					it %= x;
					if (k < cur_cnt) {
						output(out, a);
						return;
					}
					k -= cur_cnt;
					if (it <= 0) {
						if (k == 0) {
							output(out, a);
							return;
						}
						--k;
						it += x;
					}
					break;
				}
			}

		}
	}
	for (auto& it : a) {
		if (it == 0) {
			if (k == 0) {
				output(out, a);
				return;
			}
			--k;
			it += x;
		}
	}
	std::set<pli> vals;
	int index = 0;
	for (const auto& it : a) {
		vals.emplace(abs(it), index++);
	}
	while (k > 0) {
		auto it = *vals.begin();
		vals.erase(vals.begin());
		const int index = it.second;
		if (a[index] < 0) {
			a[index] -= x;
		}
		else {
			a[index] += x;
		}
		--k;
		vals.emplace(abs(a[index]), index);
	}
	output(out, a);

}

#include "Head.h"
#include "maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111;

int ans;
vector<int> a, divs, vec, best;

int get_cnt() {
	vector<int> dp(MAXN, INF);
	dp[0] = 0;
	for (int i = 0; i < MAXN; ++i) {
		for (const auto& div : vec) {
			if (i + div >= MAXN) {
				break;
			}
			umin(dp[i + div], dp[i] + 1);
		}
	}
	int res = 0;
	for (const auto& it : a) {
		if (dp[it] == INF) {
			return INF;
		}
		res += dp[it];
	}
	return res;
}

ll get(ll val) {
	ll res = 0;
	reverse(all(vec));
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] > val) {
			continue;
		}
		res += val / vec[i];
		val %= vec[i];
	}
	reverse(all(vec));
	return res;
}

ll get_fast() {
	ll res = 0;
	for (const auto& it : a) {
		res += get(it);
	}
	return res;
}

void go(const int pos) {
	bool any = false;
	for (int i = pos + 1; i < divs.size(); ++i) {
		if (divs[i] % divs[pos] == 0) {
			any = true;
			vec.emplace_back(divs[i]);
			go(i);
			vec.pop_back();
		}
	}
	if (!any) {
		const int cur = get_fast();
		if (umin(ans, cur)) {
			best = vec;
		}
	}
}

void solve(istream& in, ostream& out) {
	int n;
	in >> n;
	a.resize(n);
	in >> a;

	sort(all(a));
	ans = INF;
	for (const auto& it : a) {
		divs.clear();
		for (int i = 1; i <= it; ++i) {
			if (it % i == 0) {
				divs.emplace_back(i);
			}
		}
		vec = { 1 };
		go(0);
	}
	out << ans << endl;
	return;
	for (const auto& it : best) {
		out << it << " ";
	}
	out << endl;

	/* for (int test = 0; test < 100; ++test) {
		int n = Random::get(1, 7);
		a.resize(n);
		for (int i = 0; i < n; ++i) {
			a[i] = Random::get(1, 100);
		}
		sort(all(a));
		out << "Test #" << test << ": " << n << endl;
		for (const auto& it : a) {
			out << it << " ";
		}
		out << endl;
		ans = INF;
		divs = { 1 };
		vec = { 1 };
		for (const auto& it : a) {
			for (int i = 2; i <= it; ++i) {
				if (it % i == 0) {
					divs.emplace_back(i);
				}
			}
		}
		sort(all(divs));
		divs.resize(unique(all(divs)) - divs.begin());
		go(0);
		out << ans << endl;
		for (const auto& it : best) {
			out << it << " ";
		}
		out << endl << endl;
	} */
}

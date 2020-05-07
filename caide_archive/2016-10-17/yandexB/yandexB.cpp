#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111;
const int MAXM = 111111;

int dp[MAXN][MAXM];

namespace brute {

	const int MAXN = 1e2 + 5;

	int p[MAXN];
	int n;
	bool f;

	bool good(std::istream& in, std::ostream& out, int lim) {
		ll my = lim, bonus = 0;
		for (int i = 0; i < n; i++) {
			if (p[i] <= my) {
				if (f) out << p[i] << " + 0" << endl;
				my -= p[i];
				bonus += p[i] / 100;
			}
			else {
				if (my + bonus < p[i]) return 0;
				ll lim = min(bonus, 1ll * p[i]);
				if (f) out << (p[i] - lim) << " + " << lim << endl;
				my -= p[i] - lim;
				bonus -= lim;
			}
		}
		return 1;
	}
	void solve(std::istream& in, std::ostream& out) {
		in >> n;
		for (int i = 0; i < n; i++) in >> p[i];
		int lf = 1, rg = 1e9;
		f = 0;
		while (lf + 1 < rg) {
			int md = (lf + rg) >> 1;
			if (good(in, out, md)) rg = md;
			else lf = md;
		}
		int ans;
		if (good(in, out, lf)) ans = lf;
		else ans = rg;
		out << ans << endl;
		f = 1;
		good(in, out, ans);
	}

}  // namespace brute

using Strategy = std::function<int(const std::vector<int>&, std::istream&, std::ostream&, bool)>;

namespace alex {

	void print(const int sum, const std::vector<int>& ans, const std::vector<int>& a, std::istream& in, std::ostream& out) {
		const int n = a.size();
		out << sum << endl;
		int total_money = 0;
		int total_bonus = 0;
		for (int i : range(n)) {
			const int money = ans[i];
			const int bonus = a[i] - money;
			out << money << " + " << bonus << endl;
			assert(money + bonus == a[i]);
			assert(money >= 0);
			assert(money <= a[i]);
			assert(bonus <= total_bonus);
			if (bonus == 0) {
				total_bonus += money / 100;
			}
			total_money += money;
			total_bonus -= bonus;
		}
		assert(total_money == sum);
	}

}

int stupid_strategy(const std::vector<int>& a, std::istream& in, std::ostream& out, bool dry_run) {
	const int n = a.size();
	vector<int> prefsum(n + 1);
	for (int i : range(n)) {
		prefsum[i + 1] = prefsum[i] + a[i] / 100;
	}
	vector<int> ans = a;
	int bottom = 0;
	for (int i : downrange(n)) {
		if (prefsum[i + 1] == bottom) {
			break;
		}
		if (prefsum[i] < bottom) {
			bottom -= a[i] / 100;
		}
		else {
			const int rest = min(a[i], prefsum[i] - bottom);
			ans[i] = a[i] - rest;
			bottom += rest;
		}
	}

	int sum = 0;
	for (int it : ans) {
		sum += it;
	}
	if (!dry_run) {
		alex::print(sum, ans, a, in, out);
	}
	return sum;
}

int damn_strategy(const std::vector<int>& a, std::istream& in, std::ostream& out, bool dry_run) {
	const int n = a.size();
	vector<int> prefsum(n + 1);
	for (int i : range(n)) {
		prefsum[i + 1] = prefsum[i] + a[i] / 100;
	}
	vector<int> ans = a;
	int bottom = 0;
	int bottom_sum = 0;
	for (int i : downrange(n)) {
		if (prefsum[i + 1] == bottom || i == 0) {
			break;
		}
		if (a[i] / 100 <= bottom) {
			const int tmp_bottom = bottom - a[i] / 100;
			if (prefsum[i - 1] >= tmp_bottom) {
				if (prefsum[i - 1] <= a[i - 1] + tmp_bottom) {
					ans[i] = a[i];
					bottom_sum += ans[i];
					bottom = tmp_bottom;
					continue;
				}
			}
		}
		if (prefsum[i] < bottom) {
			bottom -= a[i] / 100;
		}
		else {
			const int rest = min(a[i], prefsum[i] - bottom);
			ans[i] = a[i] - rest;
			bottom += rest;
		}
		bottom_sum += ans[i];
	}

	int sum = 0;
	for (int it : ans) {
		sum += it;
	}
	if (!dry_run) {
		alex::print(sum, ans, a, in, out);
	}
	return sum;
}

int forward_strategy(const std::vector<int>& a, std::istream& in, std::ostream& out, bool dry_run) {
	const int n = a.size();
 	vector<int> sufsum(n + 1);
	for (int i : downrange(n)) {
		sufsum[i] = sufsum[i + 1] + a[i];
	}
	vector<int> ans = a;
	int top_bonus = 0;
	for (int i : range(n)) {
		const int cur_bonus = a[i] / 100;
		if (top_bonus + cur_bonus > sufsum[i + 1]) {
			const int rest = std::max(0, a[i] - top_bonus);
			ans[i] = rest;
			top_bonus -= a[i] - rest;
		}
		else {
			top_bonus += cur_bonus;
		}
	}

	int sum = 0;
	for (int it : ans) {
		sum += it;
	}
	if (!dry_run) {
		alex::print(sum, ans, a, in, out);
	}
	return sum;
}

namespace nastya {

	bool good(const std::vector<int>& p, std::istream& in, std::ostream& out, int lim, bool dry_run) {
		const int n = p.size();
		ll my = lim, bonus = 0;
		for (int i = 0; i < n; i++) {
			if (p[i] <= my) {
				if (!dry_run) out << p[i] << " + 0" << endl;
				my -= p[i];
				bonus += p[i] / 100;
			}
			else {
				if (my + bonus < p[i]) return 0;
				ll lim = min(bonus, 1ll * p[i]);
				if (!dry_run) out << (p[i] - lim) << " + " << lim << endl;
				my -= p[i] - lim;
				bonus -= lim;
			}
		}
		return 1;
	}

}

int nastya_strategy(const std::vector<int>& p, std::istream& in, std::ostream& out, bool dry_run) {
	int lf = 1, rg = 1e9;
	while (lf + 1 < rg) {
		int md = (lf + rg) >> 1;
		if (nastya::good(p, in, out, md, true)) rg = md;
		else lf = md;
	}
	int ans;
	if (nastya::good(p, in, out, lf, true)) ans = lf;
	else ans = rg;
	if (!dry_run) {
		out << ans << endl;
		nastya::good(p, in, out, ans, dry_run);
	}
	return ans;
}

void solve(std::istream& in, std::ostream& out) {
	// brute::solve(in, out); return;
	int n;
	in >> n;
	vector<int> a(n);
	in >> a;

	vector<Strategy> strategies{
		stupid_strategy,
		// damn_strategy,
		// forward_strategy,
		nastya_strategy
	};

	vector<int> values;
	for (const auto& strategy : strategies) {
		const int answer = strategy(a, in, out, true);
		values.emplace_back(answer);
	}
	
	const auto min_elem_iter = min_element(values.begin(), values.end());
	const auto strategy_iter = strategies.begin() + std::distance(values.begin(), min_elem_iter);
	const Strategy strategy = *strategy_iter;
	strategy(a, in, out, false);
}

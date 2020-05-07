#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

std::vector<int> get_people(const int mask) {
	std::vector<int> people;
	int tmp_mask = mask;
	while (tmp_mask > 0) {
		const int v = ctz(tmp_mask);
		tmp_mask ^= (1 << v);
		people.emplace_back(v);
	}
	return people;
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<vector<double>> prob(n, vector<double>(n));
	in >> prob;
	vector<vector<double>> dp(1 << n, vector<double>(n));
	for (int i : range(n)) {
		prob[i][i] = 1;
		dp[0][i] = 1;
	}
	for (int mask : range(1 << n)) {
		for (int i : range(n)) {
			if (mask & (1 << i)) {
				continue;
			}
			const int nmask = mask ^ (1 << i);
			if (mask == 0) {
				dp[nmask][i] = 1;
				continue;
			}
			const auto people = get_people(mask);
			const auto vec = get_people(nmask);
			double cur = 0;
			for (const auto& it : people) {
				cur += dp[mask][it] * prob[i][it];
			}
			umax(dp[nmask][i], cur);
			for (const auto& it : people) {
				umax(dp[nmask][it], dp[mask][it] * prob[it][i]);
			}
		}
	}
	out << fixed << setprecision(16) << dp.back().front() << endl;
}

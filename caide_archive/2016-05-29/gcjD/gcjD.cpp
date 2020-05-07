#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

bool workday(const std::vector<int>& a, const std::vector<int>& order, std::vector<bool>& used, const int pos) {
	const int n = a.size();
	if (pos == n) {
		return true;
	}
	bool worked = false;
	for (int i = 0; i < n; ++i) {
		if ((a[order[pos]] & (1 << i)) && !used[i]) {
			used[i] = true;
			if (!workday(a, order, used, pos + 1)) {
				return false;
			}
			used[i] = false;
			worked = true;
		}
	}
	return worked;
}

bool check(const std::vector<int>& a) {
	const int n = a.size();
	std::vector<int> order(n);
	std::iota(all(order), 0);
	bool ok = true;
	do {
		vector<bool> used(n, false);
		ok &= workday(a, order, used, 0);
	} while (next_permutation(all(order)));
	return ok;
}

int go(std::vector<int>& a, const int pos) {
	const int n = a.size();
	if (pos == n) {
		return check(a) ? 0 : INF;
	}
	const int init = a[pos];
	int ret = INF;
	for (int mask = 0; mask < (1 << n); ++mask) {
		if ((mask & init) != init) {
			continue;
		}
		if (mask == 2) {
			mask = 2;
		}
		if (mask == 6) {
			mask = 6;
		}
		const int cur = popcount(mask ^ init);
		a[pos] = mask;
		const int value = go(a, pos + 1);
		umin(ret, cur + value);
	}
	a[pos] = init;
	return ret;
}

int solve(std::vector<int>& a) {
	return go(a, 0);
}

void solve(istream& in, ostream& out) {
	input_txt();
	in >> __;
	for (int _ = 1; _ <= __; ++_) {
		std::cerr << _ << std::endl;
		out << "Case #" << _ << ": ";
		int n;
		in >> n;
		vector<int> a(n);
		for (int i = 0; i < n; ++i) {
			std::string s;
			in >> s;
			int cur = 0;
			for (int j = 0; j < n; ++j) {
				cur = (cur << 1) ^ (s[j] == '1' ? 1 : 0);
			}
			a[i] = cur;
		}
		int ans = solve(a);
		out << ans << endl;
	}
}

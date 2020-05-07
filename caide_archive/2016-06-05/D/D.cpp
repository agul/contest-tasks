#include "Head.h"
#include "mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

inline ModInt<int> C(const std::vector<ModInt<int>>& fact, const std::vector<ModInt<int>>& inv, const int n, const int k) {
	return fact[n] * inv[k] * inv[n - k];
}

inline bool check(int x, int y, int p) {
	if ((x & 1) == (y & 1)) {
		return true;
	}
	x /= 2;
	y /= 2;
	if (x >= p || y >= p) {
		return false;
	}
	return x == y;
}

int brute(const int m, const int w, const int p) {
	std::vector<int> perm;
	for (int i = 0; i < m; ++i) {
		perm.emplace_back(i * 2);
	}
	for (int i = 0; i < w; ++i) {
		perm.emplace_back(i * 2 + 1);
	}
	int ans = 0;
	std::sort(perm.begin(), perm.end());
	do {
		bool ok = true;
		for (int i = 1; i < perm.size(); ++i) {
			ok &= check(perm[i - 1], perm[i], p);
		}
		ans += (ok ? 1 : 0);
	} while (next_permutation(perm.begin(), perm.end()));
	return ans;
}

int solve(const std::vector<ModInt<int>>& fact, const std::vector<ModInt<int>>& inv, const int m, const int w, const int p) {
	if (m == 0 || w == 0) {
		return fact[m + w].value();
	}
	ModInt<int> ans = 0;
	for (int pairs = 0; pairs <= p; ++pairs) {
		const int alone_w = w - pairs;
		const int alone_m = m - pairs;
		{
			ModInt<int> cur = 1;
			cur *= fact[pairs];
			cur *= C(fact, inv, p, pairs);

			const int places_w = (pairs >> 1) + (pairs & 1);
			cur *= (places_w == 0 ? 0 : fact[alone_w + places_w - 1] * inv[places_w - 1]);

			const int places_m = (pairs >> 1) + 1;
			cur *= (places_m == 0 ? 0 : fact[alone_m + places_m - 1] * inv[places_m - 1]);

			ans += cur;

		}
		{
			ModInt<int> cur = 1;
			cur *= fact[pairs];
			cur *= C(fact, inv, p, pairs);

			const int places_m = (pairs >> 1) + (pairs & 1);
			cur *= (places_m == 0 ? 0 : fact[alone_m + places_m - 1] * inv[places_m - 1]);

			const int places_w = (pairs >> 1) + 1;
			cur *= (places_w == 0 ? 0 : fact[alone_w + places_w - 1] * inv[places_w - 1]);

			ans += cur;

		}

	}
	return ans.value();
}

void solve(istream& in, ostream& out) {
	std::vector<ModInt<int>> fact(MAXN * 2);
	std::vector<ModInt<int>> inv(MAXN * 2);

	fact[0] = inv[0] = 1;
	for (size_t i = 1; i < fact.size(); ++i) {
		fact[i] = fact[i - 1] * i;
		inv[i] = fact[i].inverse();
	}
	int m, w, p;
	in >> m >> w >> p;
	int ans = solve(fact, inv, m, w, p); out << ans << endl; return;
	for (m = 0; m <= 10; ++m) {
		for (w = 0; w <= 10; ++w) {
			for (p = 0; p <= min(m, w); ++p) {
				if (m + w == 0 || m + w > 10) {
					continue;
				}
				int pans = solve(fact, inv, m, w, p);
				int jans = brute(m, w, p);
				if (pans != jans) {
					std::cerr << "WTF!!! " << m << " " << w << " " << p << " " << jans << " " << pans << std::endl;
				}
			}
		}
	}
	std::cerr << "OK" << std::endl;
	// out << pans << endl;
}

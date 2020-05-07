#include "Head.h"
#include "mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111111;

ModInt<int> c(const std::vector<ModInt<int>>& fact, const std::vector<ModInt<int>>& inv, int n, int k) {
	if (n < k) {
		return 0;
	}
	return fact[n] * inv[k] * inv[n - k];
}

void solve(istream& in, ostream& out) {
	in >> __;
	vector<ModInt<int>> fact(MAXN);
	vector<ModInt<int>> inv(MAXN);
	fact.front() = inv.front() = 1;
	for (int i = 1; i < MAXN; ++i) {
		fact[i] = fact[i - 1] * i;
		inv[i] = fact[i].inverse();
	}
	for (int _ = 0; _ < __; ++_) {
		int n, k;
		in >> n >> k;
		vector<int> a(n);
		in >> a;
		const size_t zeroes = count(all(a), 0);
		const size_t non_zeroes = n - zeroes;
		ModInt<int> ans = 0;
		const size_t start = (zeroes == 0 ? k & 1 : 0);
		const size_t delta = (zeroes == 0 ? 2 : 1);
		for (size_t i = start; i <= k; i += delta) {
			ans += c(fact, inv, non_zeroes, i);
		}
		out << ans << endl;
	}
}

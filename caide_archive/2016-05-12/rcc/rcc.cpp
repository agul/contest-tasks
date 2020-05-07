#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 20;

ll update_ans(const std::vector<int>& pref, const int div) {
	ll res = 0;
	int last = 0;
	for (int j = 0, k = 0; j < MAXN; j += div, ++k) {
		res += static_cast<ll>(k) * (pref[j] - last);
		last = pref[j];
	}
	return res;
}

void solve(istream& ins, ostream& out) {
	vector<vector<int>> divisors(MAXN);
	for (int i = 1; i < MAXN; ++i) {
		for (int j = i; j < MAXN; j += i) {
			divisors[j].emplace_back(i);
		}
	}
	int n, m;
	io >> n >> m;
	vector<int> a(n);
	vector<int> cnt(MAXN, 0);
	for (auto& it : a) {
		io >> it;
		++cnt[it];
	}
	vector<int> pref(MAXN, 0);
	for (int i = 1; i < MAXN; ++i) {
		pref[i] = pref[i - 1] + cnt[i];
	}
	vector<ll> ans(MAXN, 0);
	for (int i = 1; i < MAXN; ++i) {
		ans[i] = update_ans(pref, i);
	}
	for (int i = 0; i < m; ++i) {
		int tp, val;
		io >> tp >> val;
		if (tp == 3) {
			io << ans[val] << endl;
			continue;
		}
		if (tp == 1) {
			int& cur = a[val - 1];
			--cnt[cur];
			++cnt[cur + 1];
			--pref[cur];
			for (const auto& div : divisors[cur]) {
				ans[div] = update_ans(pref, div);
			}
			++cur;
		}
		else {
			int& cur = a[val - 1];
			--cur;
			++cnt[cur];
			--cnt[cur + 1];
			++pref[cur];
			for (const auto& div : divisors[cur]) {
				ans[div] = update_ans(pref, div);
			}
		}
	}
}

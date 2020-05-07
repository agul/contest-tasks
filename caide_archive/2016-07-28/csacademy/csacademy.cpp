#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<ll> a(n);
	vector<int> p(n);
	in >> a >> p;
	for (auto& it : p) {
		--it;
	}
	ll sum = std::accumulate(all(a), 0LL);
	vector<ll> pref(n + 1);
	pref[0] = 0;
	partial_sum(all(a), pref.begin() + 1);
	std::multiset<ll, std::greater<ll>> sums;
	sums.emplace(sum);
	std::set<pii> vals;
	vals.emplace(pii( 0, n - 1 ));
	for (const auto& pos : p) {
		const ll ans = *sums.begin();
		out << ans << endl;
		auto it = vals.lower_bound({pos, pos});
		if (it == vals.end() || it->first > pos) {
			--it;
		}
		const int L = it->first;
		const int R = it->second;
		vals.erase(it);
		sums.erase(sums.find(pref[R + 1] - pref[L]));
		if (pos > L) {
			vals.emplace(L, pos - 1);
			sums.emplace(pref[pos] - pref[L]);
		}
		if (pos < R) {
			vals.emplace(pos + 1, R);
			sums.emplace(pref[R + 1] - pref[pos + 1]);
		}
	}
}

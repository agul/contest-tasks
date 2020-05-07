#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	vector<ll> a(3);
	in >> a;
	const ll min_days = *max_element(a);
	const ll sum = std::accumulate(all(a), 0LL);
	ll ans = LINF;
	for (int i : range(4)) {
		for (int j : range(4)) {
			for (ll day = std::max(0LL, min_days - 2); day <= min_days + 2; ++day) {
				vector<ll> b(3, day);
				for (int k : range(i)) {
					b[2 - k]++;
				}
				for (int k : range(j)) {
					b[k]++;
				}
				bool ok = true;
				for (int k : range(3)) {
					ok &= (b[k] >= a[k]);
				}
				if (ok) {
					umin(ans, std::accumulate(all(b), 0LL) - sum);
				}
			}
		}
	}
	if (min_days <= 1) {
		for (int start : range(3)) {
			for (int finish : range(start, 4)) {
				vector<ll> b(3);
				for (int k : range(start, finish)) {
					++b[k];
				}

				bool ok = true;
				for (int k : range(3)) {
					ok &= (b[k] >= a[k]);
				}
				if (ok) {
					umin(ans, std::accumulate(all(b), 0LL) - sum);
				}
			}
		}
	}
	out << ans << endl;
}

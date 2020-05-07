#include "Head.h"
#include "maths.hpp"
#include "mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111111;

class Warrior {
public:
	ll a, b, c;

	Warrior() = default;

	friend istream& operator >>(istream& in, Warrior& rhs) {
		in >> rhs.a >> rhs.b >> rhs.c;
		return in;
	}

};

void solve(istream& in, ostream& out) {
	int n;
	ll m;
	in >> n >> m;
	vector<Warrior> a(n);
	in >> a;
	vector<int> lose(MAXN);
	vector<ll> sum(n + 1);
	for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1] + a[i - 1].b;
	}
	int battle = 0;
	for (int i = 0; i < MAXN; ++i) {
		while (battle < n && sum[battle] + i < MAXN && a[battle].a < sum[battle] + i) {
			++battle;
		}
		if (battle == n || sum[battle] + i >= MAXN) {
			for (int j = i; j < MAXN; ++j) {
				lose[j] = n;
			}
			break;
		}
		lose[i] = battle;
	}
	ll ans = 0;
	std::vector<bool> used(MAXN);
	int pos = 0;
	ll strength = m;
	while (true) {
		if (strength >= MAXN) {
			ans += n;
			break;
		}
		if (used[strength]) {
			out << -1 << endl;
			return;
		}
		used[strength] = true;
		const int pos = lose[strength];
		if (pos == n) {
			ans += n;
			break;
		}
		ans += pos + 1;
		strength += sum[pos] - a[pos].c;
		umax(strength, ll(0));
	}
	out << ans << endl;
}

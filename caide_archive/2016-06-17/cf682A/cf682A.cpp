#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

inline ll get(const int n, int mod) {
	if (mod == 0) {
		mod = 5;
	}
	const int full = n / 5;
	const int rem = n % 5 >= mod ? 1 : 0;
	return full + rem;
}

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	ll ans = 0;
	for (int i = 1; i <= 5; ++i) {
		ans += get(n, i % 5) * get(m, (5 - i) % 5);
	}
	out << ans << endl;
}

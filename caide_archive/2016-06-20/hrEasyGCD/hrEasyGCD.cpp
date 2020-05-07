#include "base/header.hpp"
#include "maths/maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<int> a(n);
	in >> a;
	int g = a.front();
	for (const auto& it : a) {
		g = gcd(g, it);
	}
	std::vector<int> primes;
	primes_vector(MAXN, &primes);
	std::vector<int> divs;
	int min_div = -1;
	for (const auto& it : primes) {
		if (g % it == 0) {
			min_div = it;
			break;
		}
	}
	if (min_div == -1) {
		min_div = g;
	}
	const int ans = k / min_div * min_div;
	out << ans << endl;
}

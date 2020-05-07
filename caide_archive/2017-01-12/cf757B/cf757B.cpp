#include "base/header.hpp"
#include "maths/maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> a(n);
	in >> a;
	vector<int> primes_div;
	min_prime_div_vector(MAXN, &primes_div);
	vector<int> divs(MAXN, 0);
	for (const auto& it : a) {
		int cur = it;
		while (cur > 1) {
			const int min_div = primes_div[cur];
			while (cur % min_div == 0) {
				cur /= min_div;
			}
			divs[min_div] += 1;
		}
	}
	int ans = 1;
	for (int it : divs) {
		if (it == 0) {
			continue;
		}
		umax(ans, it);
	}
	out << ans << endl;
}

#include "base/header.hpp"
#include "maths/maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111111;

void solve(std::istream& in, std::ostream& out) {
	std::vector<int> divs;
	min_prime_div_vector(MAXN, &divs);
	std::vector<int> cnt_divs(MAXN, 0);
	int n, k;
	in >> n >> k;
	std::vector<bool> ok(MAXN);
	for (int i : range(n)) {
		int x;
		in >> x;
		int tmp = x;
		while (tmp > 1) {
			const int div = divs[tmp];
			int cnt = 0;
			while (tmp % div == 0) {
				++cnt;
				tmp /= div;
			}
			umax(cnt_divs[div], cnt);
		}
	}
	bool ans = true;
	int tmp = k;
	while (tmp > 1) {
		const int div = divs[tmp];
		int cnt = 0;
		while (tmp % div == 0) {
			++cnt;
			tmp /= div;
		}
		ans &= (cnt_divs[div] >= cnt);
	}
	out << (ans ? "Yes" : "No") << endl;
}

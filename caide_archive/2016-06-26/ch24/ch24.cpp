#include "base/header.hpp"
#include "maths/mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 20000010;

using Num = ModInt<int, 104857601>;

int r[MAXN];
Num c[MAXN];
char s[MAXN];

double start;

void solve(std::istream& in, std::ostream& out) {
	in >> s;
	start = clock();

	const int n = strlen(s);
	for (int i = 0; i <= n; ++i) {
		r[i] = -n;
	}
	for (int i = 0; i <= n; ++i) {
		c[i] = 0;
	}
	r[0] = 0;
	c[0] = 1;
	for (int i = 0; i < n; ++i) {
		if (i % 10000 == 0) {
			std::cerr << i << " / " << n << " " << (clock() - start) / CLOCKS_PER_SEC << std::endl;
		}
		if (s[i] == '(') {
			for (int i = n; i >= 1; --i) {
				const int x = r[i - 1] + 1;
				if (umax(r[i], x)) {
					c[i] = c[i - 1];
				}
				else if (x == r[i]) {
					c[i] += c[i - 1];
				}
			}
		}
		else {
			for (int i = 0; i < n; ++i) {
				const int x = r[i + 1] + 1;
				if (umax(r[i], x)) {
					c[i] = c[i + 1];
				}
				else if (x == r[i]) {
					c[i] += c[i + 1];
				}
			}
		}
	}
	std::cerr << n << " / " << n << std::endl;
	// return c[0];

	out << c[0] << endl;
}

#include "Head.h"
#include "mod_int.hpp"
#include "string_utils.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	int n;
	in >> n;
	for (int i = 0; i < n; ++i) {
		const string s = to_string(i);
		const size_t ls = s.length();
		ModInt<int, 2> sum;
		for (int mask = 0; mask < (1 << ls); ++mask) {
			ModInt<int, 2> cur = !!popcount(mask);
			for (int i = 0; i < ls; ++i) {
				if (mask & (1 << i)) {
					cur *= dig(s[i]);
				}
			}
			sum += cur;
		}
		if (sum == 0) {
			out << i << ", ";
		}
	}
}

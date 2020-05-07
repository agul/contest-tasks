#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	in >> __;
	for (int _ = 0; _ < __; ++_) {

		ll n;
		in >> n;
		--n;
		string ans;
		while (n > 0) {
			ans += '0' + n % 5 * 2;
			n /= 5;
		}
		reverse(all(ans));
		out << (ans.empty() ? "0" : ans) << endl;
	}
}

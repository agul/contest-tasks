#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

ll pows[16];

int composite(ll n) {
	for (ll i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return i;
		}
	}
	return 0;
}

int check(int base, ll n) {
	for (ll i = 2; i * i <= n; ++i) {
		ll rem = n % i;
		ll rem_base = pows[base] % i;
		mul_mod(rem, rem_base, i);
		add_mod(rem, 1LL, i);
		if (rem == 0) {
			return i;
		}
	}
	return 0;
}

int K = 16;

void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	int n, m;
	io >> n >> m;
	n -= 2;
	for (ll i = 2; i <= 10; ++i) {
		pows[i] = ppow(i, n - K + 1);
	}
	io << "Case #1: " << endl;
	for (int mask = 0; mask < (1 << K) && m > 0; ++mask) {
		vector<int> ans;
		for (int base = 2; base <= 10; ++base) {
			ll number = 1;
			for (int i = 0; i < K; ++i) {
				number = number * base + ((mask & (1 << i)) > 0 ? 1 : 0);
			}
			int value = check(base, number);
			if (value > 0) {
				ans.emplace_back(value);
			}
			else {
				break;
			}
		}
		if (ans.size() != 9) {
			continue;
		}
		io << '1';
		for (int i = 0; i < K; ++i) {
			io << ((mask & (1 << i)) > 0 ? 1 : 0);
		}
		for (int i = 0; i < n - K; ++i) {
			io << '0';
		}
		io << "1 ";
		for (const auto& it : ans) {
			io << it << ' ';
		}
		io << endl;
		--m;
		cerr << m << endl;
	}
}

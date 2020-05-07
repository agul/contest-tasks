#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111;

using Container = unordered_map<ll, int>;

ll need;
ll suf[MAXN], can[MAXN];

void solve(istream& ins, ostream& out) {
	int n;
	io >> n >> need;
	vector<ll> a(n);
	for (auto& it : a) {
		io >> it;
	}
	suf[n] = 0;
	can[n] = 1;
	for (int i = n - 1; i >= 0; --i) {
		suf[i] = suf[i + 1] + (a[i] == 1 ? 0 : a[i]);
		if (can[i + 1] < need) {
			can[i] = can[i + 1] * a[i];
		}
		else {
			can[i] = can[i + 1];
		}
	}
	vector<Container> num(n + 1);
	num[0][0] = 1;
	for (int i = 0; i < n; ++i) {
		for (const auto& it : num[i]) {
			ll cur_mul = 1;
			for (int j = i; j < n; ++j) {
				cur_mul *= a[j];
				if (cur_mul > need) {
					break;
				}
				ll cur_res = it.first + cur_mul;
				if (cur_res + suf[j + 1] > need || cur_res + can[j + 1] + n - j < need) {
					continue;
				}
				num[j + 1][cur_res] += it.second;
			}
		}
	}
	io << num[n][need] << endl;
}

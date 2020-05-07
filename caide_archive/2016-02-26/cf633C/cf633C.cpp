#include "Head.h"
#include "IO/IO.h"
#include "Hasher.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 11111;
const int MAXM = 111111;

int dp[MAXN];
char s[MAXN], t[MAXN];
string a[MAXM];
Hasher<DoubleHasher_t> hasher(MAXN);
unordered_map<pli, int> str;

void solve(istream& ins, ostream& out) {
	srand(time(nullptr));
	int ls;
	io >> ls >> s;
	reverse(s, s + ls);
	for (int i = 0; i < ls; ++i) {
		s[i] = lowerCase(s[i]);
	}
	int n;
	io >> n;
	str.clear();
	for (int i = 1; i <= n; ++i) {
		io >> t;
		int lt = strlen(t);
		a[i] = string(t, t + lt);
		for (int j = 0; j < lt; ++j) {
			t[j] = lowerCase(t[j]);
		}
		hasher.hashString(t, lt);
		ll cur_hash = static_cast<ll>(hasher.getHash(1, lt));
		str[{cur_hash, lt}] = i;
	}
	hasher.hashString(s, ls);
	fill(dp, -1);
	dp[0] = 0;
	for (int i = 1; i <= ls; ++i) {
		for (int j = max(0, i - 1000); j < i; ++j) {
			if (dp[j] == -1) {
				continue;
			}
			ll cur_hash = static_cast<ll>(hasher.getHash(j + 1, i));
			pli cur_pair = { cur_hash, i - j };
			if (str.count(cur_pair)) {
				dp[i] = str[cur_pair];
				break;
			}
		}
	}
	vector<int> ans;
	int cur_index = ls;
	while (cur_index > 0) {
		int cur_str = dp[cur_index];
		ans.emplace_back(cur_str);
		cur_index -= a[cur_str].length();
	}
	for (const auto& it : ans) {
		io << a[it] << ' ' ;
	}
	io << endl;
}

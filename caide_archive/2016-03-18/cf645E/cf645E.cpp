#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2222222;

int dp[MAXN], n, used[MAXN], best;
char s[MAXN];
string ans;

void gen(int pos, int cnt) {
	if (pos == n) {
		dp[0] = 0;
		for (char ch = 'a'; ch <= 'a' + cnt; ++ch) {
			used[ch] = -1;
		}
		for (int i = 0; i < n; ++i) {
			char cur_char = s[i];
			dp[i + 1] = dp[i];
			add_mod(dp[i + 1], dp[i]);
			if (used[cur_char] == -1) {
				add_mod(dp[i + 1], 1);
			} else {
				sub_mod(dp[i + 1], dp[used[cur_char]]);
			}
			used[cur_char] = i;
		}
		if (umax(best, dp[n])) {
			ans = string(s);
		}
		return;
	}
	for (int i = 0; i < cnt; ++i) {
		s[pos] = 'a' + i;
		gen(pos + 1, cnt);
	}
}

void solve(istream& ins, ostream& out) {
	/* int cnt;
	io >> n >> cnt;
	best = 0;
	ans = "";
	fill(s, 0);
	gen(0, cnt);
	io << best << " " << ans << endl; */

	int n, k;
	io >> n >> k >> s;
	--k;
	int ls = strlen(s);
	vector<int> last_occurrence(256, -1);
	for (int i = 0; i < ls; ++i) {
		last_occurrence[s[i]] = i;
	}
	for (int i = 0; i < n; ++i) {
		int mn = INF;
		char best = 0;
		for (char ch = 'a'; ch <= 'a' + k; ++ch) {
			if (umin(mn, last_occurrence[ch])) {
				best = ch;
			}
		}
		last_occurrence[best] = i + ls;
		s[i + ls] = best;
	}
	n += ls;
	dp[0] = 0;
	for (char ch = 'a'; ch <= 'a' + k; ++ch) {
		used[ch] = -1;
	}
	for (int i = 0; i < n; ++i) {
		char cur_char = s[i];
		dp[i + 1] = dp[i];
		add_mod(dp[i + 1], dp[i]);
		if (used[cur_char] == -1) {
			add_mod(dp[i + 1], 1);
		}
		else {
			sub_mod(dp[i + 1], dp[used[cur_char]]);
		}
		used[cur_char] = i;
	}
	add_mod(dp[n], 1);
	io << dp[n] << endl;
}

#include "base/header.hpp"
#include "string_utils.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 777;

int prefix[MAXN];

void solve(std::istream& in, std::ostream& out) {
	int ls, n, x;
	string s;
	in >> ls >> s >> n;
	std::vector<pair<string, int>> a(n);
	in >> a >> x;
	std::vector<std::set<int>> pos(ls);
	for (int i = 0; i < n; ++i) {
		string tmp = a[i].first + "#" + s;
		prefixFunction(prefix, tmp);
		const int len = a[i].first.length();
		int start = len + 1;
		for (int index = start; index < tmp.length(); ++index) {
			if (prefix[index] == len) {
				pos[index - start].emplace(i);
			}
		}
	}
	ll ans = 0;
	for (int iter = 0; iter < x; ++iter) {
		vector<int> dp(ls + 1);
		vector<int> last(ls + 1);
		vector<int> mx(ls + 1);
		for (int i = 0; i < ls; ++i) {
			for (int j : pos[i]) {
				if (umax(dp[i + 1], dp[mx[i - a[j].first.length() + 1]] + a[j].second)) {
					last[i + 1] = j;
				}
			}
			mx[i + 1] = mx[i];
			if (dp[i + 1] > dp[mx[i + 1]]) {
				mx[i + 1] = i + 1;
			}
		}
		ans += dp[mx[ls]];
		int cur_pos = mx[ls];
		while (cur_pos > 0) {
			int xx = last[cur_pos];
			pos[cur_pos - 1].erase(last[cur_pos]);
			cur_pos -= a[xx].first.length();
			cur_pos = mx[cur_pos];
		}
	}
	out << ans << endl;
}

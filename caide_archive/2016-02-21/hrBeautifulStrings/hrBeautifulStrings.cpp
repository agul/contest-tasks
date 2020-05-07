#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111111;

char s[MAXN];

void solve(istream& ins, ostream& out) {
	io >> s;
	int ls = strlen(s);
	int cur_ind = 0;
	vector<int> groups;
	vector<char> val;
	while (cur_ind < ls) {
		int y = cur_ind;
		while (y < ls && s[y] == s[cur_ind]) {
			++y;
		}
		groups.emplace_back(y - cur_ind);
		val.emplace_back(s[cur_ind]);
		cur_ind = y;
	}
	ll ans = groups.size();
	ans *= (ans - 1);
	ans >>= 1;
	int cur = 0;
	for (const auto& it : groups) {
		if (it > 1) {
			++ans;
		}
		else
			if (cur > 0 && cur < val.size() - 1 && val[cur - 1] == val[cur + 1]) {
				--ans;
			}
		++cur;
	}
	io << ans << endl;
}

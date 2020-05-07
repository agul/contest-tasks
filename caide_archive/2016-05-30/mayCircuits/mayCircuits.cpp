#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

int calc(const std::string& s, const char ch) {
	int ans = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (i + 1 < s.length() && s[i] == ch && s[i + 1] == ch) {
			++ans;
			++i;
		}
	}
	return ans;
}

void solve(istream& ins, ostream& out) {
	ins >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		std::string s;
		ins >> n >> s;
		int ans = std::max(calc(s, 'B'), calc(s, 'G'));
		out << ans << endl;
	}
}

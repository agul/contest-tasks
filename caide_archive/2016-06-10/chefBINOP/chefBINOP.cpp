#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		string s, t;
		in >> s >> t;
		int a = count(all(s), '1');
		int b = count(all(t), '1');
		if (a == s.length() || a == 0) {
			out << "Unlucky Chef" << endl;
			continue;
		}
		out << "Lucky Chef" << endl;
		if (a > b) {
			a = s.length() - a;
			b = s.length() - b;
			for (auto& it : s) {
				it ^= 1;
			}
			for (auto& it : t) {
				it ^= 1;
			}
		}
		int diff = b - a;
		int ans = diff;
		for (size_t i = 0; i < s.length() && diff > 0; ++i) {
			if (t[i] == '1' && s[i] == '0') {
				--diff;
				s[i] = '1';
			} 
		}
		for (size_t i = 0; i < s.length(); ++i) {
			if (t[i] == '0' && s[i] == '1') {
				++ans;
			}
		}
		out << ans << endl;
	}
}

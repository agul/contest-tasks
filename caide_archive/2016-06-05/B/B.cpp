#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	/* unordered_set<string> a;
	string s, t;
	in >> s >> t;
	for (int i = 1; i <= s.length(); ++i) {
		for (int j = 0; j < t.length(); ++j) {
			std::string tmp = s.substr(0, i) + t.substr(j);
			if (a.count(tmp)) {
				out << "DUPLICATE: " << tmp << endl;
			}
			a.emplace(tmp);
		}
	}
	out << a.size() << endl; */
	std::string s, t;
	in >> s >> t;
	vector<int> cnt(256, 0);
	for (const auto& it : t) {
		++cnt[it];
	}
	--cnt[t.back()];
	ll ans = static_cast<ll>(s.length()) * t.length();
	for (const auto& it : s) {
		ans -= cnt[it];
	}
	ans += cnt[s.front()];
	out << ans << endl;
}

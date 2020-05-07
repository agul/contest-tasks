#include "Head.h"
#include "maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

int lcp(const std::string& s, const std::string& t) {
	int len = std::min(s.length(), t.length());
	for (int i = 0; i < len; ++i) {
		if (s[i] != t[i]) {
			return i;
		}
	}
	return len;
}

inline ll fine(const int len) {
	return 1LL << (40 - len);
}

inline ll fine(const std::string& s) {
	return fine(s.length());
}

void solve(istream& in, ostream& out) {
	int n;
	in >> n;
	vector<string> a(n);
	in >> a;
	sort(all(a));
	vector<int> p(n);
	for (int i = 1; i < n; ++i) {
		p[i] = lcp(a[i - 1], a[i]);
	}
	vector<vector<int>> last(n, vector<int>(41, -1));
	for (int i = n - 1; i >= 0; --i) {
		if (i == n - 1) {
			for (int j = 0; j <= a.back().length(); ++j) {
				last.back()[j] = n - 1;
			}
			continue;
		}
		last[i] = last[i + 1];
		for (int j = p[i + 1] + 1; j <= 40; ++j) {
			last[i][j] = -1;
		}
		for (int j = 0; j <= p[i + 1]; ++j) {
			umax(last[i][j], i + 1);
		}

		for (int j = 0; j <= a[i].length(); ++j) {
			umax(last[i][j], i);
		}
	}
	vector<ll> pref(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		pref[i + 1] = pref[i] + fine(a[i]);
	}
	vector<string> ans;
	for (int i = 0; i < n; ) {
 		int next_ind = i + 1;
		const std::string& s = a[i];
		ll delta = 0;
		int best = s.length();
		for (int len = 1; len <= s.length(); ++len) {
			if (last[i][len] == -1) {
				continue;
			}
			int val = last[i][len];
			ll cur_fine = pref[val + 1] - pref[i];
			ll new_fine = fine(len);
			if (umax(delta, cur_fine - new_fine)) {
				best = len;
				next_ind = val + 1;
			}
		}
		ans.emplace_back(s.substr(0, best));
		i = next_ind;
	}

	assert(!ans.empty());


	ll res = 0;
	for (const auto& it : ans) {
		res += fine(it);
	}
	out << res << endl;
	out << ans.size() << endl;
	for (const auto& it : ans) {
		out << it << endl;
	}
}

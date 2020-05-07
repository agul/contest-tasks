#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	std::string s;
	getline(in, s);
	std::vector<int> a(s.length()), len(s.length(), 0);
	int start = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == ' ') {
			start = i + 1;
		}
		else {
			++len[start];
		}
		a[i] = start;
	}
	int L, R;
	in >> L >> R;
	for (int iter = L; iter <= R; ++iter) {
		int ans = 0;
		int index = 0;
		while (index < s.length()) {
			if (ans != 0) {
				++ans;
			}
			ans += len[index];
			index += iter;
			if (index < s.length()) {
				index = a[index];
			}
		}
		out << ans << endl;
	}
}

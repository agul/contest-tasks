#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	string s;
	in >> n >> s;
	vector<int> ans;
	int new_block = true;
	for (const auto& it : s) {
		if (it == 'W') {
			new_block = true;
			continue;
		}
		if (new_block) {
			ans.emplace_back(0);
			new_block = false;
		}
		++ans.back();
	}
	out << ans.size() << endl;
	for (const auto& it : ans) {
		out << it << " ";
	}
	out << endl;
}

#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	string s;
	in >> s;
	vector<int> a(256, 0);
	for (auto& it : s) {
		++a[it];
	}
	vector<int> b(256, 0);
	const string t = "Bulbbasaur";
	for (auto& it : t) {
		++b[it];
	}
	int cnt = INF;
	for (auto& it : t) {
		umin(cnt, a[it] / b[it]);
	}
	out << cnt << endl;
}

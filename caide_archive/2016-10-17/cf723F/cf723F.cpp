#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m, s, t, ds, dt;
	in >> n >> m;
	vector<pii> a(m);
	in >> a >> s >> t >> ds >> dt;
	vector<pii> filtered;
	for (const auto& it : a) {
		if (it.first != s && it.first != t && it.second != s && it.second != t) {
			filtered.emplace_back(it);
		}
	}

}

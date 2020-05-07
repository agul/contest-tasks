#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 333333;

set<int> apps[MAXN];

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	for (int i : range(n)) {
		apps[i].clear();
	}
	int ans = 0;
	set<pii> notes;
	vector<int> times;
	times.reserve(m);
	for (int i : range(m)) {
		int t, x;
		in >> t >> x;
		--x;
		if (t == 1) {
			++ans;
			apps[x].emplace(i);
			notes.emplace(i, x);
			times.emplace_back(i);
		}
		else if (t == 2) {
			for (const auto& it : apps[x]) {
				notes.erase({ it, x });
			}
			ans -= apps[x].size();
			apps[x].clear();
		}
		else {
			const int finish = times[x];
			while (!notes.empty() && notes.begin()->first <= finish) {
				auto it = notes.begin();
				const int id = it->second;
				apps[id].erase(apps[id].begin());
				notes.erase(notes.begin());
				--ans;
			}
		}
		out << ans << endl;
	}
}

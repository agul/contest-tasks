#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	set<int> unused;
	int two = 2;
	vector<int> twos, threes;
	for (int i = 1; i <= n; ++i) {
		if (!(two % 3)) {
			unused.insert(two);
			two += 2;
		}
		twos.emplace_back(two);
		two += 2;
	}
	int three = 3;
	for (int i = 1; i <= m; ++i) {
		if (unused.count(three)) {
			three += 3;
		}
		threes.emplace_back(three);
		three += 3;
	}
	int two_ind = sz(twos) - 1;
	int three_ind = sz(threes) - 1;
	int ans = 0;
	while (!unused.empty() && (three_ind >= 0 && threes[three_ind] >= *unused.begin()) && (two_ind >= 0 && twos[two_ind] >= *unused.begin())) {
		int cur = *unused.begin();
		unused.erase(unused.begin());
		if (threes[three_ind] > twos[two_ind]) {
			--three_ind;
		}
		else {
			--two_ind;
		}
		umax(ans, cur);
	}
	while (!unused.empty() && (three_ind >= 0 && threes[three_ind] >= *unused.begin())) {
		int cur = *unused.begin();
		unused.erase(unused.begin());
		--three_ind;
		umax(ans, cur);
	}
	while (!unused.empty() && (two_ind >= 0 && twos[two_ind] >= *unused.begin())) {
		int cur = *unused.begin();
		unused.erase(unused.begin());
		--two_ind;
		umax(ans, cur);
	}
	if (two_ind >= 0) {
		umax(ans, twos[two_ind]);
	}
	if (three_ind >= 0) {
		umax(ans, threes[three_ind]);
	}
	io << ans << endl;
}

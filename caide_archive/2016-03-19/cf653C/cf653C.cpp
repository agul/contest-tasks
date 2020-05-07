#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

bool is_funny(const std::vector<int>& a) {
	for (size_t i = 1; i < a.size(); ++i) {
		int cur_val = 0;
		if (a[i - 1] < a[i]) {
			cur_val = -1;
		} else
			if (a[i - 1] > a[i]) {
				cur_val = 1;
			}
		int cur_need = (i & 1 ? -1 : 1);
		if (cur_val != cur_need) {
			return false;
		}
	}
	return true;
}

unordered_set<pii> checked;

bool check(std::vector<int>& a, int x, int y) {
	if (x < 0 || y < 0 || x >= a.size() || y >= a.size() || checked.count({ min(x, y), max(x, y) })) {
		return false;
	}
	checked.emplace(min(x, y), max(x, y));
	swap(a[x], a[y]);
	bool ret = is_funny(a);
	swap(a[x], a[y]);
	return ret;
}

inline bool rel(const std::vector<int>& a, int x) {
	if (x <= 0 || x >= a.size()) {
		return true;
	}
	int need = (x & 1 ? -1 : 1);
	int val = 0;
	if (a[x - 1] < a[x]) {
		val = -1;
	}
	else 
	if (a[x - 1] > a[x]) {
		val = 1;
	}
	return val == need;
}

bool fast_check(std::vector<int>& a, int x, int y) {
	if (x < 0 || y < 0 || x >= a.size() || y >= a.size() || checked.count({ min(x, y), max(x, y) })) {
		return false;
	}
	checked.emplace(min(x, y), max(x, y));
	swap(a[x], a[y]);
	bool ret = true;
	ret &= rel(a, x);
	ret &= rel(a, x + 1);
	ret &= rel(a, y);
	ret &= rel(a, y + 1);
	swap(a[x], a[y]);
	return ret;
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	checked.clear();
	vector<int> a(n);
	for (auto& it : a) {
		io >> it;
	}
	vector<int> diff;
	for (int i = 1; i < n; ++i) {
		if (!rel(a, i)) {
			diff.emplace_back(i);
		}
	}
	if (diff.size() > 4) {
		io << 0 << endl;
		return;
	}
	if (diff.size() == 4) {
		if (diff[0] + 1 == diff[1] && diff[2] + 1 == diff[3]) {
			if (check(a, diff[0], diff[2])) {
				io << 1 << endl;
				return;
			}
		}
		io << 0 << endl;
		return;
	}
	if (diff.size() == 3) {
		int ans = 0;
		if (diff[0] + 1 == diff[1]) {
			ans += (check(a, diff[0], diff[2]) ? 1 : 0);
			ans += (check(a, diff[0], diff[2] - 1) ? 1 : 0);
		}
		if (diff[1] + 1 == diff[2]) {
			ans += (check(a, diff[0], diff[1]) ? 1 : 0);
			ans += (check(a, diff[0] - 1, diff[1]) ? 1 : 0);
		}
		io << ans << endl;
		return;
	}
	if (diff.size() == 2) {
		int ans = 0;
		ans += (check(a, diff[0], diff[1]) ? 1 : 0);
		ans += (check(a, diff[0], diff[1] - 1) ? 1 : 0);
		ans += (check(a, diff[0] - 1, diff[1] - 1) ? 1 : 0);
		ans += (check(a, diff[0] - 1, diff[1]) ? 1 : 0);
		if (diff[0] + 1 == diff[1]) {
			for (int i = 0; i < n; ++i) {
				ans += (fast_check(a, diff[0], i) ? 1 : 0);
			}
		}
		io << ans << endl;
		return;
	}
	int ind = diff[0];
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += (fast_check(a, ind - 1, i) ? 1 : 0);
		ans += (fast_check(a, ind, i) ? 1 : 0);
	}
	io << ans << endl;
}

#include "base/header.hpp"
#include "maths/maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111;

static constexpr int N = 10;

int field[MAXN][MAXN];
bool used[MAXN][MAXN];
int n;
double ans;
int cnt;

std::unordered_set<int> nums;

std::set<tuple<int, int, int, int>> memo;

int rect(const int i, const int j, const int lenx, const int leny) {
	auto tp = std::make_tuple(i, j, lenx, leny);
	if (memo.count(tp)) {
		return 0;
	}
	memo.insert(tp);
	nums.clear();
	for (int x : range(i, i + lenx)) {
		for (int y : range(j, j + leny)) {
			const int color = field[x][y];
			nums.insert(color);
		}
	}
	++cnt;
	return nums.size();
}

void process(int lenx, int leny) {
	if (used[lenx][leny]) {
		return;
	}
	used[lenx][leny] = true;
	for (int i : inclusiveRange(n - lenx)) {
		for (int j : inclusiveRange(n - leny)) {
			ans += rect(i, j, lenx, leny);
		}
	}
}

void solve(std::istream& in, std::ostream& out) {
	in >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			in >> field[i][j];
			--field[i][j];
		}
	}
	fill(used, 0);
	ans = 0;
	cnt = 0;

	for (int x : inclusiveRange(1, min(n, N))) {
		for (int y : inclusiveRange(1, min(n, N))) {
			process(x, y);
		}
	}

	for (int iter : range(500)) {
		int lenx = Random::get(1, n);
		int leny = Random::get(1, n);
		int i = Random::get(0, n - lenx);
		int j = Random::get(0, n - leny);
		ans += rect(i, j, lenx, leny);
	}

	for (int x : inclusiveRange(max(1, n - N), n)) {
		for (int y : inclusiveRange(max(1, n - N), n)) {
			process(x, y);
		}
	}

	ans /= cnt;
	out << fixed << setprecision(16) << ans << endl;
}

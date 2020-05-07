#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;
const int MAXM = 55;

int get_num(char x) {
	if (x == 'I') {
		return 1;
	}
	if (x == 'V') {
		return 5;
	}
	if (x == 'X') {
		return 10;
	}
	if (x == 'L') {
		return 50;
	}
	if (x == 'C') {
		return 100;
	}
	if (x == 'D') {
		return 500;
	}
	if (x == 'M') {
		return 1000;
	}
	assert(false);
	return -1;
}

char rev_num(int x) {
	if (x == 1) {
		return 'I';
	}
	if (x == 5) {
		return 'V';
	}
	if (x == 10) {
		return 'X';
	}
	if (x == 50) {
		return 'L';
	}
	if (x == 100) {
		return 'C';
	}
	if (x == 500) {
		return 'D';
	}
	if (x == 1000) {
		return 'M';
	}
	assert(false);
	return -1;
}

bool dp[MAXM][MAXN];
char s[MAXN];

void relax(int x, int y) {
	if (y >= 0 && y <= 100000) {
		dp[x][y] = true;
	}
}

bool get(int x, int y) {
	if (y < 0 || y > 100000) {
		return false;
	}
	return dp[x][y];
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n >> s;
	int ls = strlen(s);
	vector<int> a(ls);
	for (int i = 0; i < ls; ++i) {
		a[i] = get_num(s[i]);
	}
	sort(all(a));
	int cur_ind = ls - 1;
	while (cur_ind >= 0 && a[cur_ind] == a.back()) {
		n -= a.back();
		--cur_ind;
	}
	fill(dp, false);
	dp[0][50000] = true;
	++cur_ind;
	for (int i = 0; i < cur_ind; ++i) {
		for (int j = 0; j < 100000; ++j) {
			if (!dp[i][j]) {
				continue;
			}
			relax(i + 1, j + a[i]);
			relax(i + 1, j - a[i]);
		}
	}
	n += 50000;
	if (!dp[cur_ind][n]) {
		io << "NO" << endl;
		return;
	}
	vector<char> plus, minus;
	int pos = cur_ind;
	while (pos > 0) {
		--pos;
		if (get(pos, n - a[pos])) {
			n -= a[pos];
			plus.emplace_back(rev_num(a[pos]));
		}
		else {
			n += a[pos];
			minus.emplace_back(rev_num(a[pos]));
		}
	}
	for (const auto& ch : minus) {
		io << ch;
	}
	for (int i = cur_ind; i < ls; ++i) {
		io << rev_num(a.back());
	}

	for (const auto& ch : plus) {
		io << ch;
	}
	io << endl;
}

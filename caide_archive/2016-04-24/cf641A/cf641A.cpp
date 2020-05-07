#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

char s[MAXN];
bool used[MAXN];

void solve(istream& ins, ostream& out) {
	int n;
	io >> n >> s;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	fill(used, 0);
	int cur = 0;
	while (cur >= 0 && cur < n && !used[cur]) {
		used[cur] = true;
		if (s[cur] == '<') {
			cur -= a[cur];
		}
		else {
			cur += a[cur];
		}
	}
	if (cur < 0 || cur >= n) {
		io << "FINITE" << endl;
	}
	else {
		io << "INFINITE" << endl;
	}
}

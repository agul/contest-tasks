#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 3333;

int next_zero[MAXN][MAXN];
bool a[MAXN][MAXN];
char s[MAXN];

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	for (int i = 1; i <= n; ++i) {
		io >> s;
		for (int j = 0; j < m; ++j) {
			a[i][j + 1] = (s[j] == 'z');
		}
	}
	for (int i = 1; i <= n; ++i) {
		
	}
}

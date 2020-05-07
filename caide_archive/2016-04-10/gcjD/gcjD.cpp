#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	io >> __;
	for (int test = 1; test <= __; ++test) {
		cerr << test << endl;
		int k, c, s;
		io >> k >> c >> s;
		io << "Case #" << test << ": ";
		if (k != s) {
			io << "IMPOSSIBLE" << endl;
			continue;
		}
		for (int i = 0; i < k; ++i) {
			io << i + 1 << ' ';
		}
		io << endl;
	}
}

#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	ins >> n;
	vector<string> a(n);
	for (auto& it : a) {
		ins >> it;
	}
	reverse(all(a));
	set<string> used;
	for (const auto& it : a) {
		if (!used.count(it)) {
			used.insert(it);
			out << it << endl;
		}
	}
}

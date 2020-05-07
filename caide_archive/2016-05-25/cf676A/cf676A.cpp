#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<int> a(n);
	for (auto& it : a) {
		io >> it;
	}
	
	const int min_ind = std::min_element(all(a)) - a.begin();
	const int max_ind = std::max_element(all(a)) - a.begin();

	const int ans = std::max({min_ind, max_ind, abs(max_ind - min_ind), n - 1 - min_ind, n - 1 - max_ind});
	io << ans << endl;
}

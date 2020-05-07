#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> a(n);
	in >> a;
	if (std::accumulate(all(a), 0) == n - 1) {
		out << "YES" << endl;
	}
	else {
		out << "NO" << endl;
	}
}

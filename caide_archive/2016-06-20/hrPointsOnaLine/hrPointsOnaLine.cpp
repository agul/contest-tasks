#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> x(n), y(n);
	for (int i = 0; i < n; ++i) {
		in >> x[i] >> y[i];
	}
	if (*max_element(x) == *min_element(x) || *max_element(y) == *min_element(y)) {
		out << "YES" << endl;
		return;
	}
	out << "NO" << endl;
}

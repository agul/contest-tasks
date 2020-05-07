#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<int> a(n);
	in >> a;
	int init = std::accumulate(all(a), 0);
	for (int i : range(1, n)) {
		if (a[i - 1] + a[i] < k) {
			a[i] += k - a[i] - a[i - 1];
		}
	}
	out << std::accumulate(all(a), 0) - init << endl;
	for (const auto& it : a) {
		out << it << " ";
	}
	out << endl;
}

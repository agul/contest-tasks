#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		in >> n;
		vector<int> a(n);
		in >> a;
		sort(a);
		ll sum = std::accumulate(all(a), 0LL);
		if (a.front() > 2 && a.back() == 5 && sum >= 4 * n) {
			out << "Yes" << endl;
			continue;
		}
		out << "No" << endl;
	}
}

#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	vector<int> a(n);
	in >> a;
	auto inp = a;
	vector<int> b(m);
	for (int i : a) {
		if (i <= m) {
			b[i - 1]++;
		}
	}
	const int ans = n / m;
	for (int i : range(m)) {
		if (b[i] < ans) {
			for (int& x : a) {
				if (x > m || b[x - 1] > ans) {
					if (x <= m) {
						--b[x - 1];
					}
					x = i + 1;
					++b[i];
					if (b[i] == ans) {
						break;
					}
				}
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] != inp[i]) {
			++cnt;
		}
	}
	out << ans << " " << cnt << endl;
	for (const auto& it : a) {
		out << it << " ";
	}
	out << endl;
}

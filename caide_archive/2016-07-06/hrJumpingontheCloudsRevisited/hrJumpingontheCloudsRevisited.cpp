#include "base/header.hpp"
#include "maths/mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<int> a(n);
	in >> a;
	int index = 0;
	int e = 100;
	while (index != 0 || (index == 0 && e == 100)) {
		--e;
		add_mod(index, k, n);
		if (a[index] == 1) {
			e -= 2;
		}
	}
	out << e << endl;
}

#include "base/header.hpp"
#include "maths/mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<ll> a(n);
	in >> a;
	sort(a);
	if (a.front() == 1 && a.back() == 1) {
		out << "0/1" << endl;
		return;
	}
	bool odd = true;
	for (const auto& it : a) {
		if ((it & 1) == 0) {
			odd = false;
		}
	}
	ModInt<int> q = 2;
	for (const auto& it : a) {
		q = binpow(q, it);
	}
	q *= ModInt<int>(2).inverse();
	ModInt<int> p = q;
	if (!odd) {
		p += 1;
	}
	else {
		p -= 1;
	}
	p *= ModInt<int>(3).inverse();
	out << p << "/" << q << endl;
}

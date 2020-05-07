#include "base/header.hpp"
#include "maths/mod_int.hpp"
#include "maths/polynom.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using Num = ModInt<int, 786433>;
using Poly = Polynom<Num>;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	Poly a(n);
	in >> a >> __;
	for (int _ : range(__)) {
		Num x;
		in >> x;
		const Num ans = a(x);
		out << ans << endl;
	}
}

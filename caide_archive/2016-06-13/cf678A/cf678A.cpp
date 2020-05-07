#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	ll n, k;
	in >> n >> k;
	out << n + k - n % k << endl;
}

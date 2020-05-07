#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

const ll COEF = 100000;

void solve(std::istream& in, std::ostream& out) {
	string s, t;
	double inc1, inc2;
	double mul;
	in >> s >> inc1 >> t >> mul >> inc2;
	double val = inc1 * mul;
	if (fabs(val - inc2) < EPS) {
		out << "Whatever" << endl;
	} else if (val + EPS < inc2) {
		out << "Evolve, Power up" << endl;
	}
	else {
		out << "Power up, Evolve" << endl;
	}
}

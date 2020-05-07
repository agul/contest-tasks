#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	bool color = false;
	for (int i : range(n)) {
		for (int j : range(m)) {
			char ch;
			in >> ch;
			if (ch == 'M' || ch == 'Y' || ch == 'C') {
				color = true;
			}
		}
	}
	out << (color ? "#Color" : "#Black&White") << endl;
}

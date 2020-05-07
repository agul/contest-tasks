#include "base/header.hpp"
#include "graph/dsu.hpp"

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using namespace std;

int n, m;

unsigned int checksum(const char str[], int len) {
	unsigned int r = 0;
	for (int k = 0; k<8 * len; k++) { // iterate over bits of str
		if ((r & (1 << 31)) != 0) r = (r << 1) ^ 0x04c11db7;
		else r = (r << 1); // do some magic
		if (str[k / 8] & 1 << (7 - k % 8)) // if the k-th bit of str is set,
			r ^= 1; // then flip the last bit of r
	}
	return r;
}

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		string s;
		in >> s;
		out << checksum(s.c_str(), s.length()) << endl;
		out << ((65 << 24) ^ (66 << 16) ^ (99 << 8) ^ (100)) << endl;
	}
}

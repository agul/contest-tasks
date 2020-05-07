#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

const std::string init = "AbdHIMOoTUVvWwXxYp";
const std::string rev  = "AdHIMOoTUVvWwXxYq";

void solve(std::istream& in, std::ostream& out) {
	string s;
	in >> s;
	const int len = s.length();
	const int mid = (len + 1) / 2;
	for (int i = 0; i < mid; ++i) {
		const char x = s[i];
		const char y = s[len - i - 1];
		const int posx = init.find(x);
		const int posy = rev.find(y);
		if (posx == std::string::npos || posx != posy) {
			out << "NIE" << endl;
			return;
		}
	}
	out << "TAK" << endl;
}

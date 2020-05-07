#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	string s;
	in >> s;
	if (s.back() == 'E') {
		out << s.length() - 1 << endl;
		return;
	}
	if (s.front() == 'E') {
		out << 0 << endl;
		return;
	}
	for (int i : range(s.length())) {
		if (s[i] == 'E' && s[i + 1] == 'E') {
			out << i + 1 << endl;
			return;
		}
	}
	for (int i : downrange(s.length())) {
		if (s[i] == 'E') {
			out << i << endl;
			return;
		}
	}
}

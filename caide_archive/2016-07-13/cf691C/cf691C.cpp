#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void output(std::ostream& out, const std::string& a, const std::string& b, int deg) {
	assert(a.length() == 1);
	assert(a.front() >= '1' && a.front() <= '9');
	out << a;
	if (!b.empty()) {
		out << "." << b;
	}
	if (deg != 0) {
		out << "E" << deg;
	}
	out << endl;
}

void solve(std::istream& in, std::ostream& out) {
	string s, a, b;
	in >> s;
	const int len = s.length();
	int cur_ind = 0;
	while (cur_ind < len && s[cur_ind] != '.') {
		a += s[cur_ind];
		++cur_ind;
	}
	++cur_ind;
	while (cur_ind < len) {
		b += s[cur_ind];
		++cur_ind;
	}

	while (!b.empty() && b.back() == '0') {
		b.pop_back();
	}
	if (a.empty()) {
		a = "0";
	}

	int deg = 0;
	
	int zero = 0;
	while (zero < a.length() && a[zero] == '0') {
		++zero;
	}
	if (zero >= a.length()) {
		int index = 0;
		while (index < b.length() && b[index] == '0') {
			++index;
		}
		a = b.substr(index, 1);
		b = b.substr(index + 1);
		output(out, a, b, -(index + 1));
		return;
	}
	a = a.substr(zero);

	if (a.length() > 1) {
		deg += a.length() - 1;
		b = a.substr(1) + b;
		a = a.substr(0, 1);
	}

	while (!b.empty() && b.back() == '0') {
		b.pop_back();
	}

	output(out, a, b, deg);

}

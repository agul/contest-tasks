#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	std::string s;
	in >> s;
	int x = s.find('.');
	int y = s.find('e');
	int deg = 0;
	if (y != std::string::npos) {
		deg = std::stoi(s.substr(y + 1));
		s = s.substr(0, y);
	}
	if (x == std::string::npos) {
		s += '.';
		x = s.length() - 1;
	}
	std::string a = s.substr(0, x);
	std::string b = s.substr(x + 1);
	if (deg > 0) {
		if (b.length() <= deg) {
			a += b;
			deg -= b.length();
			b = "";
			a += std::string(deg, '0');
		}
		else {
			a += b.substr(0, deg);
			b = b.substr(deg);
		}
	}
	else {
		deg = abs(deg);
		if (a.length() <= deg) {
			b = a + b;
			deg -= a.length();
			a = std::string(deg, '0');
			b = a + b;
			a = "";
		}
		else {
			b = a.substr(a.length() - deg) + b;
			a = a.substr(0, a.length() - deg);
		}
	}
	while (!b.empty() && b.back() == '0') {
		b.pop_back();
	}
	while (!a.empty() && a.front() == '0') {
		a.erase(a.begin());
	}
	if (a.empty()) {
		a = "0";
	}
	assert(a == "8549");
	out << a;
	if (!b.empty()) {
		out << "." << b;
	}
	out << endl;

}

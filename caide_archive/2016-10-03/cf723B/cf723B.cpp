#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	string s;
	in >> n >> s;
	bool brackets = false;
	int ax = 0;
	int ay = 0;
	int cur_word = 0;
	for (const auto& it : s) {
		if (isalpha(it)) {
			++cur_word;
		}
		else {
			if (brackets) {
				ay += (cur_word > 0 ? 1 : 0);
			}
			else {
				umax(ax, cur_word);
			}
			if (it == '(') {
				brackets = true;
			}
			else if (it == ')') {
				brackets = false;
			}
			cur_word = 0;
		}
	}
	umax(ax, cur_word);
	out << ax << " " << ay << endl;
}

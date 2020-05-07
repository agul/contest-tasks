#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

inline char winner(char x, char y) {
	if (x > y) {
		swap(x, y);
	}
	if (x == 'P' && y == 'R') {
		return 'P';
	}
	if (x == 'P' && y == 'S') {
		return 'S';
	}
	if (x == 'R' && y == 'S') {
		return 'R';
	}
	return '$';
}

inline bool check(const int p, const int r, const int s) {
	const int n = r + p + s;
	return max({ abs(r - s), abs(r - p), abs(p - s) }) == 1 && (n & (n - 1)) == 0 && n > 1;
}

std::string get_ans(const int p, const int r, const int s) {
	if (!check(p, r, s)) {
		return "";
	}
	if (p == 1 && r == 1 && s == 0) {
		return "PR";
	}
	if (p == 1 && r == 0 && s == 1) {
		return "PS";
	}
	if (p == 0 && r == 1 && s == 1) {
		return "RS";
	}
	const int n = p + r + s;
	if (n % 3 == 1) {
		return get_ans(p / 2 + p % 2, r / 2, s / 2)
			+ get_ans(p / 2, r / 2 + r % 2, s / 2)
			+ get_ans(p / 2, r / 2, s / 2 + s % 2);
	}
	return get_ans(p / 2 + p % 2, r / 2 + r % 2, s / 2)
		+ get_ans(p / 2 + p % 2, r / 2, s / 2 + s % 2)
		+ get_ans(p / 2, r / 2 + r % 2, s / 2 + s % 2);
}

void solve(istream& in, ostream& out) {
	input_txt();
	in >> __;
	for (int _ = 1; _ <= __; ++_) {
		std::cerr << _ << std::endl;
		out << "Case #" << _ << ": ";
		int n, r, p, s;
		in >> n >> r >> p >> s;
		std::string ans = get_ans(p, r, s);
		out << (ans.empty() ? "IMPOSSIBLE" : ans) << endl;
	}
}

#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

int get(const int pos, const int k) {
	return pos + (pos - 1) / k * 5;
}

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<string> a(n);
	string password;
	in >> a >> password;
	sort(a, [](const std::string& lhs, const std::string& rhs) {
		return lhs.length() < rhs.length();
	});
	const int len = password.length();
	int cnt_less = 0;
	int cnt_eq = 0;
	for (const auto& it : a) {
		if (it.length() < len) {
			++cnt_less;
		} else if (it.length() == len) {
			++cnt_eq;
		}
	}
	out << get(cnt_less + 1, k) << " " << get(cnt_less + cnt_eq, k) << endl;
}

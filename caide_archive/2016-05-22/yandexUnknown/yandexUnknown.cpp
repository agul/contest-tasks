#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int diff(const std::string& s, const std::string& t) {
	int cnt = 0;
	for (size_t i = 0; i < s.length(); ++i) {
		cnt += (s[i] == t[i] ? 0 : 1);
	}
	return cnt;
}

void solve(istream& ins, ostream& out) {
	int n;
	ins >> n;
	vector<string> a(n);
	for (auto& it : a) {
		ins >> it;
	}
	for (const auto& s : a) {
		bool ok = true;
		for (const auto& t : a) {
			ok &= (diff(s, t) <= 1);
		}
		if (ok) {
			out << s << endl;
			return;
		}
	}
}

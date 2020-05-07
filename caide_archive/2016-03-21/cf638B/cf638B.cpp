#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 32;

char t[MAXN];

void solve(istream& ins, ostream& out) {
	// io.assign_files_input_txt();
	int n;
	io >> n;
	set<string> a;
	for (int i = 0; i < n; ++i) {
		io >> t;
		a.emplace(t);
	}
	set<string> new_a;
	for (const auto& str : a) {
		bool ok = true;
		for (const auto& it : a) {
			if (it != str && it.find(str) != string::npos) {
				ok = false;
				break;
			}
		}
		if (ok) {
			new_a.emplace(str);
		}
	}
	a.swap(new_a);
	string ans = "";
	while (!a.empty()) {
		string append = "";
		size_t common = 0;
		for (const auto& it : a) {
			size_t pos = ans.find(it[0]);
			if (pos == string::npos) {
				continue;
			}
			common = ans.length() - pos;
			append = it;
			break;
		}
		if (common == 0) {
			for (const auto& it : a) {
				bool found = true;
				for (const auto& jt : a) {
					if (it == jt) {
						continue;
					}
					if (jt.find(it[0]) != string::npos) {
						found = false;
					}
				}
				if (found) {
					append = it;
					break;
				}
			}
		}
		a.erase(append);
		append.erase(0, common);
		ans += append;
		set<string> new_a;
		for (const auto& it : a) {
			if (ans.find(it) == string::npos) {
				new_a.emplace(it);
			}
		}
		a.swap(new_a);
	}
	io << ans.c_str() << endl;
}

#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

using Set = std::set<pair<int, char>, greater<pair<int, char>>>;

bool check(const Set& a, const int sum) {
	return a.begin()->first > sum / 2;
}


void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	io >> __;
	for (int _ = 1; _ <= __; ++_) {
		cerr << _ << endl;
		io << "Case #" << _ << ": ";
		int n;
		io >> n;
		Set a;
		int sum = 0;
		for (int i = 0; i < n; ++i) {
			int x;
			io >> x;
			sum += x;
			a.emplace(x, 'A' + i);
		}
		while (sum > 0) {
			std::string ans = "";
			auto it = *a.begin();
			a.erase(a.begin());
			--sum;
			ans += it.second;
			if (--it.first > 0) {
				a.emplace(it);
			}
			if (sum == 0) {
				io << ans;
				break;
			}

			Set b(a);
			it = *a.begin();
			a.erase(a.begin());
			--sum;
			ans += it.second;
			if (--it.first > 0) {
				a.emplace(it);
			}
			if (sum == 0) {
				io << ans;
				break;
			}

			if (check(a, sum)) {
				ans = ans.substr(0, 1);
				a.swap(b);
				++sum;
			}



			if (check(a, sum)) {
				std::cerr << "WTF???" << std::endl;
			}

			io << ans << " ";

		}
		io << endl;
	}
}

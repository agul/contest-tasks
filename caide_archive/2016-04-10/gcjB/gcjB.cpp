#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

inline void xor_ch(char& ch) {
	ch = (ch == '+' ? '-' : '+');
}

void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	ins >> __;
	for (int test = 1; test <= __; ++test) {
		cerr << test << endl;
		io << "Case #" << test << ": ";
		string s;
		ins >> s;
		int ans = 0;
		for (;;) {
			int cur_ind = s.length() - 1;
			while (cur_ind >= 0 && s[cur_ind] == '+') {
				--cur_ind;
			}
			if (cur_ind < 0) {
				break;
			}
			int zero = cur_ind;
			cur_ind = 0;
			while (cur_ind < zero && s[cur_ind] == '+') {
				++cur_ind;
			}
			std::reverse(s.begin(), s.begin() + cur_ind);
			for (int i = 0; i < cur_ind; ++i) {
				xor_ch(s[i]);
			}
			if (cur_ind > 0) {
				++ans;
			}
			std::reverse(s.begin(), s.begin() + zero + 1);
			++ans;
			for (int i = 0; i < zero + 1; ++i) {
				xor_ch (s[i]);
			}
		}
		io << ans << endl;
	}
}

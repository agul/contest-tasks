#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2222;

const char * W[] = { "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE" };

int res, ans[MAXN], dig_cnt[16][256], ls, cnt[256], len[16], dlen[16];
char s[MAXN], dedup[16][8];

bool go(int pos) {
	if (pos == ls) {
		return true;
	}
	for (int i = 0; i < 10; ++i) {
		bool ok = true;
		for (int j = 0; j < dlen[i] && ok; ++j) {
			const char ch = dedup[i][j];
			ok &= cnt[ch] >= dig_cnt[i][ch];
		}
		if (ok) {
			for (int j = 0; j < dlen[i]; ++j) {
				const char ch = dedup[i][j];
				cnt[ch] -= dig_cnt[i][ch];
			}
			ans[res++] = i;
			if (go(pos + len[i])) {
				return true;
			}
			--res;
			for (int j = 0; j < dlen[i]; ++j) {
				const char ch = dedup[i][j];
				cnt[ch] += dig_cnt[i][ch];
			}
		}
	}
	return false;
}

void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	fill(dig_cnt, 0);
	for (int i = 0; i < 10; ++i) {
		len[i] = strlen(W[i]);
		for (int j = 0; j < len[i]; ++j) {
			++dig_cnt[i][W[i][j]];
		}
		std::copy(W[i], W[i] + len[i], dedup[i]);
		std::sort(dedup[i], dedup[i] + len[i]);
		auto it = std::unique(dedup[i], dedup[i] + len[i]);
		*it = 0;
		dlen[i] = it - dedup[i];
	}
	io >> __;
	for (int _ = 1; _ <= __; ++_) {
		std::cerr << _ << std::endl;
		io << "Case #" << _ << ": ";
		io >> s;
		ls = strlen(s);
		res = 0;
		fill(cnt, 0);
		for (int i = 0; i < ls; ++i) {
			++cnt[s[i]];
		}
		go(0);
		for (int i = 0; i < res; ++i) {
			io << ans[i];
		}
		io << endl;
	}
}

#include "base/header.hpp"
#include "graph/dsu.hpp"

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using namespace std;

unsigned int checksum(const char str[], int len) {
	unsigned int r = 0;
	for (int k = 0; k<8 * len; k++) { // iterate over bits of str
		if ((r & (1 << 31)) != 0) r = (r << 1) ^ 0x04c11db7;
		else r = (r << 1); // do some magic
		if (str[k / 8] & 1 << (7 - k % 8)) // if the k-th bit of str is set,
			r ^= 1; // then flip the last bit of r
	}
	return r;
}

void test() {

	vector<unsigned int> crcTable(128);
	for (unsigned int i = 0; i < 128; i++) {
		unsigned r = i << 24;

		for (int j = 0; j < 8; j++) {
			if ((r & 0x80000000) != 0) {
				r = r << 1 ^ 0x04C11DB7;
			}
			else {
				r <<= 1;
			}
		}
		crcTable[i] = r;
	}
	cerr << crcTable['A'] << " " << crcTable['q'] << endl;
	cerr << (crcTable['A'] ^ crcTable['B'] ^ crcTable['c'] ^ crcTable['d'] ^ crcTable['3']) << endl;
}

int wh[256], cnt, rev[64];
uint table[64][1000001];

void add_char(const char ch) {
	wh[ch] = cnt;
	rev[cnt] = ch;
	++cnt;
}

inline uint get(const std::string& s) {
	uint ans = 0;
	const int n = s.length();
	for (int i : range(n)) {
		const char cur = s[n - 1 - i];
		ans ^= table[wh[cur]][i];
	}
	return ans;
}

void solve(std::istream& in, std::ostream& out) {
	cnt = 0;
	for (char ch : inclusiveRange('0', '9')) {
		add_char(ch);
	}
	for (char ch : inclusiveRange('A', 'Z')) {
		add_char(ch);
	}
	for (char ch : inclusiveRange('a', 'z')) {
		add_char(ch);
	}

	for (int i : range(cnt)) {
		uint r = rev[i];

		for (int k : range(1000000)) {
			table[i][k] = r;
			for (int j = 0; j < 8; j++) {
				if ((r & 0x80000000) != 0) {
					r = r << 1 ^ 0x04C11DB7;
				}
				else {
					r <<= 1;
				}
			}
		}
	}

	in >> __;
	for (int _ : range(__)) {
		string s;
		int n;
		in >> n >> s;
		uint cur_val = get(s);
		int m;
		in >> m;
		out << cur_val << endl;
		for (int i : range(m)) {
			int x;
			char to;
			in >> x >> to;
			--x;
			const int pos = n - 1 - x;
			cur_val ^= table[wh[s[x]]][pos];
			s[x] = to;
			cur_val ^= table[wh[s[x]]][pos];
			out << cur_val << endl;
		}
	}

}

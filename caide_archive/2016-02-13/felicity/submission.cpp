#pragma comment(linker, "/STACK:66777216")
#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <utility>
#include <functional>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <queue>
#include <cmath>
#include <random>
#include <sstream>
#include <numeric>
#include <limits>
#include <chrono>
#include <type_traits>
#pragma hdrstop

using namespace std;

#ifdef _MSC_VER
#include <intrin.h>
#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif


#ifdef _MSC_VER

#endif


inline bool isDigit(const char ch) {
	return (ch >= '0' && ch <= '9');
}


class IO {
public:

	static const int IO_ERR = -1;
	static const int BUFFER_SIZE = 1 << 18;
	
	bool eof;
	char curChar;

	IO() : rbCount(0), rbOffset(0), curChar(0), eof(false) {}

	~IO() {
		fwrite(writeBuffer, sizeof(writeBuffer[0]), wbOffset, stdout);
	}


	inline int nextInt();

	IO& operator >>(int& x);

	void newline();

	void printString(const char * s);

	IO& operator <<(const char * s);
	IO& operator <<(ostream& (*fn)(ostream&));


private:
	char readBuffer[BUFFER_SIZE], writeBuffer[BUFFER_SIZE];
	size_t rbCount, rbOffset, wbOffset;

};

extern bool useFastIO;
extern istream * pin;
extern ostream * pout;
extern IO io;

inline int nextInt() {
	if (useFastIO) {
		return io.nextInt();
	}
	int ret;
	*pin >> ret;
	return ret;
}


inline void newline() {
	if (useFastIO) {
		io.newline();
		return;
	}
	*pout << endl;
}


inline void printString(const char * s) {
	if (useFastIO) {
		io.printString(s);
		return;
	}
	*pout << s;
}


int __;
IO io;

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int n, m;
		io >> n >> m;
		bool ok = false;
		for (int i = 0; i < m; ++i) {
			int from;
			int to;
			io >> from >> to;
			ok |= (from == 1 && to == n);
		}
		io << (ok ? "Jorah Mormont" : "Khal Drogo") << endl;
	}
}
#include <fstream>


extern class IO io;
bool useFastIO = false;
istream * pin;
ostream * pout;

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;
    useFastIO = true;

    ostream& out = cout;
    out << fixed << setprecision(16);
    pin = &in; pout = &out;
    solve(in, out);
    return 0;
}


namespace Random {


}


inline int IO::nextInt() {
	while (!eof && !isDigit(curChar) && curChar != '-') {
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				return IO_ERR;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	bool neg = false;
	if (curChar == '-') {
		neg = true;
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				return IO_ERR;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	int result = 0;
	while (!eof && isDigit(curChar)) {
		result = (result << 3) + (result << 1) + curChar - '0';
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				return (neg ? -result : result);
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	return (neg ? -result : result);
}


IO& IO::operator >>(int& x) {
	x = ::nextInt();
	return *this;
}


void IO::newline() {
	if (wbOffset == BUFFER_SIZE) {
		// flush begin
		fwrite(writeBuffer, sizeof(writeBuffer[0]), wbOffset, stdout);
		wbOffset = 0;
		// flush end
	}
	writeBuffer[wbOffset++] = '\n';
}


void IO::printString(const char * s) {
	for (int i = 0; s[i]; ++i) {
		if (wbOffset == BUFFER_SIZE) {
			// flush begin
			fwrite(writeBuffer, sizeof(writeBuffer[0]), wbOffset, stdout);
			wbOffset = 0;
			// flush end
		}
		writeBuffer[wbOffset++] = s[i];
	}
}


IO& IO::operator <<(const char * s) {
	::printString(s);
	return *this;
}


IO& IO::operator <<(ostream& (*fn)(ostream&)) {
	::newline();
	return *this;
}

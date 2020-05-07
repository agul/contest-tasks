#pragma comment(linker, "/STACK:66777216")
#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
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
#pragma hdrstop

using namespace std;

#ifdef _MSC_VER
#include <intrin.h>
#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#endif


#define ull unsigned long long


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


	inline ull nextUlong();

	IO& operator >>(ull& x);

	void newline();

	void printInt(int x);

	IO& operator <<(int x);
	IO& operator <<(ostream& (*fn)(ostream&));


private:
	char readBuffer[BUFFER_SIZE], writeBuffer[BUFFER_SIZE];
	size_t rbCount, rbOffset, wbOffset;

};

extern bool useFastIO;
extern istream * pin;
extern ostream * pout;
extern IO io;


inline ull nextUlong() {
	if (useFastIO) {
		return io.nextUlong();
	}
	ull ret;
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

inline void printInt(int x) {
	if (useFastIO) {
		io.printInt(x);
		return;
	}
	*pout << x;
}


IO io;


ull L, R, x;

void solve(istream& ins, ostream& out) {
	io >> L >> R >> x;
	ull p = 1;
	
	bool any = false;
	for (int i = 0; i < 1000000; ++i) {
		if (p > R) {
			break;
		}
		if (p >= L && p <= R) {
			cout << i << " " << p << endl;
			any = true;
		}
		p *= x;
	}
	if (!any) {
		io << -1;
	}
	io << endl;
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


inline ull IO::nextUlong() {
	while (!eof && !isDigit(curChar)) {
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
	ull result = 0;
	while (!eof && isDigit(curChar)) {
		result = (result << 3) + (result << 1) + curChar - '0';
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				return result;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	return result;
}


/* inline void IO::nextLine(char * s) {
	if (!curChar) {
		rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
		if (rbCount <= 0) {
			eof = true;
			return;
		}
		rbOffset = 0;
		curChar = readBuffer[rbOffset++];
	}
	int ind = 0;
	while (!eof && curChar != '\n') {
		s[ind++] = curChar;
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				s[ind] = 0;
				return;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	s[ind] = 0;
	// shiftChar begin
	if (rbOffset == rbCount) {
		rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
		if (rbCount <= 0) {
			eof = true;
			return;
		}
		rbOffset = 0;
	}
	curChar = readBuffer[rbOffset++];
	// shiftChar end
} */


IO& IO::operator >>(ull& x) {
	x = ::nextUlong();
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

void IO::printInt(int x) {
	if (wbOffset + 12 > BUFFER_SIZE) {
		// flush begin
		fwrite(writeBuffer, sizeof(writeBuffer[0]), wbOffset, stdout);
		wbOffset = 0;
		// flush end
	}
	if (x < 0) {
		writeBuffer[wbOffset++] = '-';
		x = -x;
	}
	else
	if (!x) {
		writeBuffer[wbOffset++] = '0';
		return;
	}
	int st = wbOffset;
	while (x) {
		writeBuffer[wbOffset++] = x % 10 + '0';
		x /= 10;
	}
	for (int l = st, r = wbOffset - 1; l < r; ++l, --r) {
		char t = writeBuffer[l];
		writeBuffer[l] = writeBuffer[r];
		writeBuffer[r] = t;
	}
}


IO& IO::operator <<(int x) {
	::printInt(x);
	return *this;
}


IO& IO::operator <<(ostream& (*fn)(ostream&)) {
	::newline();
	return *this;
}

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


#define ll long long

const ll LINF = 0x3f3f3f3f3f3f3f3fLL;


template<class T> 
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

template<class T> 
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

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
	inline ll nextLong();

	IO& operator >>(int& x);
	IO& operator >>(ll& x);


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


inline ll nextLong() {
	if (useFastIO) {
		return io.nextLong();
	}
	ll ret;
	*pin >> ret;
	return ret;
}


template<class T> inline T sqr(const T& x) {
	return x * x;
}


namespace Random {


}


IO io;

int n;
ll x, y, xx, yy;

#define PI 3.14159265358979323846

void solve(istream& ins, ostream& out) {
	io >> n >> xx >> yy;
	ll mn = LINF, mx = -LINF;
	for (int i = 0; i < n; ++i) {
		io >> x >> y;
		ll dst = sqr(x - xx) + sqr(y - yy);
		umax(mx, dst);
		umin(mn, dst);
	}
	out << setprecision(17) << PI * (mx - mn) << endl;
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


inline ll IO::nextLong()  {
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
	ll result = 0;
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

IO& IO::operator >>(int& x) {
	x = ::nextInt();
	return *this;
}


IO& IO::operator >>(ll& x) {
	x = ::nextLong();
	return *this;
}

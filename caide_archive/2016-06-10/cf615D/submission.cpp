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


#ifdef _MSC_VER
#endif


extern bool useFastIO;
extern istream * pin;
extern ostream * pout;


namespace Random {


}


int f(const std::vector<int>& a, const std::function<int(const int&, const int& b)>& g) {
	return std::accumulate(a.begin(), a.end(), 0, g);
}

void solve(istream& ins, ostream& out) {
	std::vector<int> a;
	for (int i = 0; i < 10; ++i) {
		a.emplace_back(rand() % 5);
	}
	for (const auto& it : a) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
	int y = 0;
	std::cout << f(a, [&y](const int& x, const int& p) {
		++y;
		return x + p;
	}) << " " << std::endl;
	std::cout << y << " " << std::endl;

}
#include <fstream>


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

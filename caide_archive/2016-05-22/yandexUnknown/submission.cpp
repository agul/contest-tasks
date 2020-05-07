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


extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;


//inline void print_string(const std::string& s);

//inline void print_line(const std::string& s);


using namespace std;


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



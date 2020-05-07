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


namespace std {


}

#ifdef _MSC_VER

#endif


namespace Random {


}


extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;


//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;


void solve(istream& ins, ostream& out) {
	int n, k, f;
	ins >> n;
	vector<int>t;
	for (int i = 0; i < n; i++)
	{
		ins >> k;
		f = 0;
		for (int j = 0; j < t.size(); j++)
			if (t[j] == k)
			{
				f = 1;
				break;
			}
		if (f == 0)
		{
			t.push_back(k);
		}
	}
	sort(t.begin(), t.end());
	for (int i = 0; i < t.size() - 2; i++)
		if ((t[i] == t[i + 1] - 1) && (t[i] == t[i + 2] - 2))
		{
			out << "YES";
			return;
		}
	out << "NO";
	return;
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

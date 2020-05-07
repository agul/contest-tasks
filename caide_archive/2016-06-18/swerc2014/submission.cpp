#pragma comment(linker, "/STACK:66777216")
#pragma warning(disable : 4996)

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#pragma hdrstop

const long long LINF = 0x3f3f3f3f3f3f3f3fLL;

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#ifdef _MSC_VER

#endif

template<typename T, size_t N>
struct MakeVector {
	
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define ll long long

#include <iterator>

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	int k;
	in >> k;
	vector<int>numb(2 * k + 1);
	vector<char>znak(2 * k + 1);
	for (int i = 1; i <= k; i++)
	{
		in >> numb[i]>>znak[i];
		numb[k + i] = numb[i];
		znak[k + i] = znak[i];
	}
	vector< vector<ll> >max_val(k + 1, vector<ll>(2*k + 1, -LINF));
	vector< vector<ll> >min_val(k + 1, vector<ll>(2*k + 1, LINF));
	for (int i = 1; i < 2*k; i++)
	{
		max_val[1][i] = numb[i];
		min_val[1][i] = numb[i];
	}
	for (int st = 2; st < k+1; st++)
	{
		for (int i = 1; i < 2*k-st+1; i++)
		{
			for (int j = i; j < i+st-1; j++)
			{
				int first = j - i + 1;
				int second = st - first;
				switch (znak[j])
				{
				case '?':
					max_val[st][i] = max(max_val[st][i], max_val[first][i] + max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] + min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] + max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] + min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] - max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] - min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] - max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] - min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] * max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] * min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] * max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] * min_val[second][j + 1]);

					min_val[st][i] = min(min_val[st][i], max_val[first][i] + max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] + min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] + max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] + min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] - max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] - min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] - max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] - min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] * max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] * min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] * max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] * min_val[second][j + 1]);
					break;
				case '+':
					max_val[st][i] = max(max_val[st][i], max_val[first][i] + max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] + min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] + max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] + min_val[second][j + 1]);

					min_val[st][i] = min(min_val[st][i], max_val[first][i] + max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] + min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] + max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] + min_val[second][j + 1]);
					break;
				case '-':
					max_val[st][i] = max(max_val[st][i], max_val[first][i] - max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] - min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] - max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] - min_val[second][j + 1]);

					min_val[st][i] = min(min_val[st][i], max_val[first][i] - max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] - min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] - max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] - min_val[second][j + 1]);
					break;
				case '*':
					max_val[st][i] = max(max_val[st][i], max_val[first][i] * max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] * min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] * max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] * min_val[second][j + 1]);

					min_val[st][i] = min(min_val[st][i], max_val[first][i] * max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] * min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] * max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] * min_val[second][j + 1]);
					break;
				default:
					break;
				}
			}
		}
	}
	for (int i = 1; i < k+1; i++)
	{
		out << abs(min_val[k][i]) << abs(max_val[k][i]);
	}
	return;
}

#include <fstream>

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}


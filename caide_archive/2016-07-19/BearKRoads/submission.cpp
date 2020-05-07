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

#include <iterator>

template<typename R>
void sort(R& range) {
	std::sort(range.begin(), range.end());
}

using namespace std;

class BearKRoads {
public:
	struct Edge {
		
		Edge(int from, int to, int cnt) : from(from), to(to), cnt(cnt) { }
		
		bool operator < (const Edge& rhs) const {
			return cnt > rhs.cnt;
		}

		int from, to;
		int cnt;
	};

    /// caide keep
    int maxHappy(vector<int> x, vector<int> a, vector<int> b, int k) {
		const int m = a.size();
		int result = 0;
		for (int i = 0; i < k; ++i) {
			std::vector<Edge> edges;
			for (int i = 0; i < m; ++i) {
				edges.emplace_back(a[i], b[i], x[a[i]] + x[b[i]]);
			}
			sort(edges);
			const auto& it = edges.front();
			result += it.cnt;
			x[it.to] = 0;
			x[it.from] = 0;
		}
        return result;
    }
};


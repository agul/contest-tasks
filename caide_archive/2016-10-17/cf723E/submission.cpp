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

static constexpr long long LINF = 0x3f3f3f3f3f3f3f3fLL;

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

template<typename T>
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

template<typename T>
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

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

#define all(a) a.begin(), a.end()

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define ll long long

#define pli std::pair<ll, int>

namespace std {

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

}  // namespace std

#include <iterator>

using namespace std;

void output(std::ostream& out, const std::vector<ll>& a) {
	for (const auto& it : a) {
		out << it << " ";
	}
	out << endl;
}

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	ll x;
	in >> n >> k >> x;
	vector<ll> a(n);
	in >> a;
	ll mx = x * k;

	int cnt_zeroes = std::count(all(a), 0);
	int cnt_negative = 0;
	ll max_negative = -LINF;
	ll min_positive = LINF;
	for (const auto& it : a) {
		if (it == 0) {
			continue;
		}
		if (it > 0) {
			umin(min_positive, it);
		}
		else {
			umax(max_negative, it);
			++cnt_negative;
		}
	}

	if (cnt_zeroes == 0 && cnt_negative % 2 == 0 && max_negative + mx <= 0 && min_positive - mx >= 0) {
		ll to_find = (abs(max_negative) < min_positive ? max_negative : min_positive);

		for (auto& it : a) {
			if (it == to_find) {
				if (it < 0) {
					it += mx;
				}
				else {
					it -= mx;
				}
				break;
			}
		}

		output(out, a);
		return;
	}

	if (cnt_negative % 2 == 0) {
		if (cnt_zeroes > 0) {
			if (k == 0) {
				output(out, a);
				return;
			}
			--k;
			for (auto& it : a) {
				if (it == 0) {
					it -= x;
					break;
				}
			}
		}
		else {
			ll cur_cnt = min_positive / x;
			for (auto& it : a) {
				if (it == min_positive) {
					it %= x;
					if (k < cur_cnt) {
						output(out, a);
						return;
					}
					k -= cur_cnt;
					if (it >= 0) {
						if (k == 0) {
							output(out, a);
							return;
						}
						--k;
						it -= x;
					}
					break;
				}
			}
		}
	}
	for (auto& it : a) {
		if (it == 0) {
			if (k == 0) {
				output(out, a);
				return;
			}
			--k;
			it += x;
		}
	}
	std::set<pli> vals;
	int index = 0;
	for (const auto& it : a) {
		vals.emplace(abs(it), index++);
	}
	while (k > 0) {
		auto it = *vals.begin();
		vals.erase(vals.begin());
		const int index = it.second;
		if (a[index] < 0) {
			a[index] += x;
		}
		else {
			a[index] -= x;
		}
		--k;
		vals.emplace(abs(a[index]), index);
	}
	output(out, a);

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


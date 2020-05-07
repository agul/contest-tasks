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


template<class T> 
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

namespace std {


}

#ifdef _MSC_VER

#endif


class ReplacingDigit {
public:
    /// caide keep
    int getMaximumStockWorth(std::vector<int> prices, std::vector<int> stickers) {
		std::vector<std::string> p;
		for (const auto& price : prices) {
			p.emplace_back(std::to_string(price));
		}
		for (int i = 8; i >= 0; --i) {
			int digit = i + 1;
			char char_digit = digit + '0';
			for (int j = 0; j < stickers[i]; ++j) {
				int max_diff = 0;
				int ind = -1;
				std::string best;
				for (int k = 0; k < p.size(); ++k) {
					const auto& it = p[k];
					std::string s = it;
					int val = std::stoi(it);
					for (auto& ch : s) {
						std::swap(ch, char_digit);
						int new_val = std::stoi(s);
						if (umax(max_diff, new_val - val)) {
							ind = k;
							best = s;
						}
						std::swap(ch, char_digit);
					}
				}
				if (max_diff == 0) {
					continue;
				}
				p[ind] = best;
			}
		}
		int result = 0;
		for (const auto& price : p) {
			result += std::stoi(price);
		}
        return result;
    }
};


namespace Random {


}


//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);

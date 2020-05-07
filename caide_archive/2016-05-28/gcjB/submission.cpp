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

#define all(a) a.begin(), a.end()

template<class T> 
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

#ifdef _MSC_VER

#endif

namespace std {

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

}  // namespace std

extern bool local_input;
extern bool local_output;

void input_txt() {
	if (!local_input) {
		freopen("input.txt", "r", stdin);
	}
	if (!local_output) {
		freopen("output.txt", "w", stdout);
	}
}

using namespace std;

int __;

double get_prob(const std::vector<double>& a) {
	using pid = std::pair<int, double>;
	std::vector<pid> states = { {0, 1} };
	for (const auto& it : a) {
		std::vector<pid> upd;
		for (const auto& state : states) {
			upd.emplace_back(state.first + 1, state.second * it);
			upd.emplace_back(state.first - 1, state.second * (1 - it));
		}
		states.swap(upd);
		upd.clear();
		sort(all(states));
		for (int i = 0, cur_ind = 0; i < states.size(); i = cur_ind) {
			double sum = 0;
			while (cur_ind < states.size() && states[i].first == states[cur_ind].first) {
				sum += states[cur_ind].second;
				++cur_ind;
			}
			upd.emplace_back(states[i].first, sum);
		}
		states.swap(upd);
	}
	double ret = 0;
	for (const auto& state : states) {
		if (state.first == 0) {
			ret += state.second;
		}
	}
	return ret;
}

void solve(istream& in, ostream& out) {
	input_txt();
	in >> __;
	for (int _ = 1; _ <= __; ++_) {
		std::cerr << _ << std::endl;
		out << "Case #" << _ << ": ";
		int n, k;
		in >> n >> k;
		vector<double> a(n);
		in >> a;
		sort(all(a));
		double ans = 0;
		for (int i = 0; i <= n - k; ++i) {
			vector<double> val;
			val.insert(val.end(), a.begin() + i, a.begin() + i + k);
			const double cur = get_prob(val);
			umax(ans, cur);
		}
		{
			for (int i = 0; i < k; ++i) {
				vector<double> val;
				val.insert(val.end(), a.begin(), a.begin() + i);
				val.insert(val.end(), a.begin() + n - k + i, a.end());
				umax(ans, get_prob(val));
			}
		}
		out << fixed << setprecision(16) << ans << endl;
	}
}

#include <fstream>

bool local_input;
bool local_output;

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;
    local_input = false;

    ostream& out = cout;
    local_output = false;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}


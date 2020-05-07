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

#define pii std::pair<int, int>

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

template<typename T>
class IntegerIterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T> {
public:
	using value_type = T;

	constexpr explicit IntegerIterator(const value_type value) : value_(value) {}

	IntegerIterator& operator++() {
		++value_;
		return *this;
	}

	constexpr value_type operator*() const {
		return value_;
	}

	constexpr bool operator ==(const IntegerIterator rhs) const {
		return value_ == rhs.value_;
	}

	constexpr bool operator !=(const IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	value_type value_;

};

template<typename T>
class IntegerRange {
public:
	using const_iterator = IntegerIterator<T>;

	constexpr IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	constexpr const_iterator begin() const {
		return const_iterator(begin_);
	}

	constexpr const_iterator end() const {
		return const_iterator(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
constexpr IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

using namespace std;

bool check(const std::vector<int>& schedule, const std::vector<int>& prepare, const int days) {
	const int m = prepare.size();
	std::vector<int> last(m, -1);
	for (int i : range(days)) {
		const int exam = schedule[i];
		if (exam == 0) {
			continue;
		}
		last[exam - 1] = i;
	}

	int passed = 0;
	int days_spent = 0;
	std::set<pii> exams;
	for (int i : range(m)) {
		if (last[i] == -1) {
			return false;
		}
		exams.emplace(last[i], i);
	}
	while (!exams.empty()) {
		const auto exam = *exams.begin();
		exams.erase(exams.begin());
		const int date = exam.first;
		const int id = exam.second;
		days_spent += prepare[id];
		if (days_spent + passed > date) {
			return false;
		}
		++passed;
	}

	return true;
}

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	vector<int> schedule(n);
	vector<int> prepare(m);
	in >> schedule >> prepare;
	if (!check(schedule, prepare, n)) {
		out << -1 << endl;
		return;
	}
	int L = 0, R = n;
	while (R - L > 1) {
		int md = (L + R) / 2;
		(check(schedule, prepare, md) ? R : L) = md;
	}
	out << R << endl;
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


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

const int INF = 0x3f3f3f3f;

template<class T> 
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

#ifdef _MSC_VER

#endif

template<typename T>
class SparseTableCmp {
public:
	using Comparator = std::function<bool(const T&, const T&)>;

	SparseTableCmp(const size_t size, const Comparator& less) :
		size_(size), less_(less), log_table_(size + 1, 0) {
		for (size_t i = 2; i <= size_; ++i) {
			log_table_[i] = log_table_[i >> 1] + 1;
		}
		data_.assign(log_table_[size_] + 1, std::vector<size_t>(size_));
	}

	void build(const std::vector<T>& vec) {
		arr_ = &vec;
		for (size_t i = 0; i < size_; ++i) {
			data_[0][i] = i;
		}
		for (size_t level = 1, step = 2; step < size_; ++level, step <<= 1) {
			for (size_t i = 0; i + step <= size_; ++i) {
				const size_t x = data_[level - 1][i];
				const size_t y = data_[level - 1][i + (step >> 1)];
				data_[level][i] = (less_(arr_->at(x), arr_->at(y)) ? x : y);
			}
		}
	}

	size_t query(const size_t left, const size_t right) const {
		const size_t level = log_table_[right - left - 1];
		const size_t x = data_[level][left];
		const size_t y = data_[level][right - (1 << level)];
		return (less_(arr_->at(x), arr_->at(y)) ? x : y);
	}

private:
	std::vector<std::vector<size_t>> data_;
	std::vector<size_t> log_table_;
	Comparator less_;
	const std::vector<T>* arr_;
	size_t size_;

};

template<typename T>
class Stack {
public:
	using value_type = T;
	using size_type = size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using rvalue = value_type&&;
	using container = std::vector<value_type>;

	Stack(const size_type max_size) : data_(container(max_size)) {
		clear();
	}

	Stack() = delete;

	Stack(const Stack&) = default;
	Stack& operator =(const Stack&) = default;
	Stack(Stack&&) = default;
	Stack& operator =(Stack&&) = default;

	reference top() {
		return data_[top_index_ - 1];
	}

	const_reference top() const {
		return data_[top_index_ - 1];
	}

	constexpr bool empty() const {
		return top_index_ == 0;
	}

	void clear() {
		top_index_ = 0;
	}

	void push(rvalue value) {
		data_[top_index_++] = std::move(value);
	}

	value_type pop() {
		return data_[--top_index_];
	}

private:
	container data_;
	size_type top_index_;

};

template<typename T>
class CmpStack {
public:
	using value_type = T;
	using size_type = size_t;
	using const_reference = const value_type&;
	using Comparator = std::function<bool(const_reference, const_reference)>;

	CmpStack(const size_type n, const Comparator& less = std::less<value_type>()) : stack_(n), less_(less) {}

	constexpr bool empty() const {
		return stack_.empty();
	}

	value_type min_value() const {
		return stack_.empty() ? 0 : stack_.top().second;
	}

	void push(const_reference element) {
		value_type cur_min = element;
		if (!stack_.empty() && less_(stack_.top().second, cur_min)) {
			cur_min = stack_.top().second;
		}
		stack_.push(std::make_pair(element, cur_min));
	}

	value_type pop() {
		return stack_.pop().first;
	}

	void clear() {
		stack_.clear();
	}

private:
	Stack<std::pair<value_type, value_type>> stack_;
	Comparator less_;

};

template<typename T>
class CmpQueue {
public:
	using value_type = T;
	using size_type = size_t;
	using const_reference = const value_type&;
	using Comparator = std::function<bool(const_reference, const_reference)>;

	CmpQueue(const size_type n, const Comparator& less = std::less<value_type>()) : a_(n, less), b_(n, less), less_(less) {}

	value_type min_value() const {
		if (a_.empty()) {
			return b_.min_value();
		}
		if (b_.empty()) {
			return a_.min_value();
		}
		const value_type a = a_.min_value();
		const value_type b = b_.min_value();
		return less_(a, b) ? a : b;
	}

	void push(const_reference element) {
		a_.push(element);
	}

	value_type pop() {
		if (b_.empty()) {
			while (!a_.empty()) {
				b_.push(a_.pop());
			}
		}
		return b_.pop();
	}

	void clear() {
		a_.clear();
		b_.clear();
	}

private:
	CmpStack<value_type> a_;
	CmpStack<value_type> b_;
	Comparator less_;
};

using namespace std;

int __;

using Row = std::vector<int>;
using Field = std::vector<Row>;

void solve(istream& in, ostream& out) {
	int n, m;
	in >> n >> m;
	Field a(n, Row(m));
	Field pref(n + 1, Row(m + 1));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			in >> a[i][j];
			pref[i + 1][j + 1] = pref[i + 1][j] + pref[i][j + 1] + a[i][j] - pref[i][j];
		}
	}
	std::vector<SparseTableCmp<int>> rows(n, SparseTableCmp<int>(m, std::greater<int>()));
	for (int i = 0; i < n; ++i) {
		rows[i].build(a[i]);
	}
	std::vector<CmpQueue<int>> vals(m, CmpQueue<int>(n, std::greater<int>()));
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		int x, y;
		in >> x >> y;
		const size_t rec_size = x * y;
		int ans = INF;

		for (int i = 0; i < n; ++i) {
			for (int j = y - 1; j < m; ++j) {
				if (i == 0) {
					vals[j].clear();
				}
				const int index = rows[i].query(j - y + 1, j + 1);
				vals[j].push(a[i][index]);
				if (i < x - 1) {
					continue;
				}
				const int best = vals[j].min_value();
				const int cur_need = rec_size * best;
				const int cur_sum = pref[i + 1][j + 1] - pref[i + 1 - x][j + 1] - pref[i + 1][j + 1 - y] + pref[i + 1 - x][j + 1 - y];
				umin(ans, cur_need - cur_sum);
				vals[j].pop();
			}
		}
		out << ans << endl;
	}
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


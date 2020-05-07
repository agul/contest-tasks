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

// using namespace std;

#ifdef _MSC_VER
#include <intrin.h>
#define clz(a) __clz(a)
#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#define X first
#define Y second
#define all(a) a.begin(), a.end()

#define ll int64_t

const long double PI = 3.14159265358979323846;


template<class T> 
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

namespace std {


}

#ifdef _MSC_VER
static uint32_t __inline __clz(uint32_t x) {
	unsigned long r = 0;
	_BitScanReverse(&r, x);
	return (31 - r);
}

#endif


template<class T> inline T sqr(const T& x) {
	return x * x;
}


namespace Random {


}


inline bool is_digit(const char ch) {
	return (ch >= '0' && ch <= '9');
}


class IO {
public:
	constexpr static const std::size_t kBufferSize = 1 << 18;

	IO() : read_bytes_count_(0), read_buffer_offset_(0), current_char_(0), eof_(false) {
		static_assert(kBufferSize > 32, "Size of a buffer must be greater than 32 due to comparison in IO::flush() method.");
	}

	~IO() {
		flush();
	}

	IO(const IO&) = delete;
	IO& operator=(const IO&) = delete;
	IO(const IO&&) = delete;
	IO& operator=(const IO&&) = delete;


	inline void shift_char();

	inline int32_t next_int();
	inline int64_t next_long();

	IO& operator >>(int32_t& x);
	IO& operator >>(int64_t& x);

	inline void flush();

	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);


	// Intended to use with std::endl.


private:
	using Buffer = std::array<char, kBufferSize>;
	Buffer read_buffer_;
	Buffer write_buffer_;
	std::size_t read_bytes_count_;
	std::size_t read_buffer_offset_;
	std::size_t write_buffer_offset_;
	bool eof_;
	char current_char_;

	inline void update_buffer();

	template<typename T>
	T read_number();


};

extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;
extern IO io;

inline int32_t next_int();
inline int64_t next_long();


//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


template<class T> class SegmentTreeCmp {
public:

	T * data;
	T * delayed;
	int offset, size, N;

	SegmentTreeCmp(const int N, const std::function<bool(const T&, const T&)>& less, const T& neutral) : N(N), less(less), neutral(neutral) {
		if (N & (N - 1)) {
			offset = 1 << (32 - clz(N)); // 32 - clz(a) + 1;
		} else {
			offset = 1 << (31 - clz(N));
		}
		size = offset << 1;
		data = new T[size];
		delayed = new T[size];
		init();
	}

	~SegmentTreeCmp() {
		delete[] data;
		delete[] delayed;
	}


	void init() {
		std::fill_n(data, size, neutral);
		std::fill_n(delayed, size, neutral);
	}


	T query(int l, int r) {
		l += offset;
		r += offset;
		T res = neutral;
		while (l <= r) {
			if (l & 1) {
				const T& cur = data[l++];
				if (less(cur, res)) {
					res = cur;
				}
			}
			if (!(r & 1)) {
				const T& cur = data[r--];
				if (less(cur, res)) {
					res = cur;
				}
			}
			l >>= 1;
			r >>= 1;
		}
		return res;
	}

	void update(int pos, const T& val) {
		pos += offset;
		data[pos] = val;
		pos >>= 1;
		while (pos >= 1) {
			const T &x = data[pos << 1], &y = data[(pos << 1) ^ 1];
			data[pos] = (less(x, y) ? x : y);
			pos >>= 1;
		}
	}


private:

	std::function<bool(const T&, const T&)> less;
	T neutral;


};


using namespace std;

IO io;
const int MAXN = 111111;

int p[MAXN];
ll wh[MAXN];

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<pair<ll, int>> a(n);
	for (int i = 0; i < n; ++i) {
		ll r, h;
		io >> r >> h;
		ll v = sqr(r) * h;
		a[i] = { v, i };
	}
	sort(all(a));
	int cur_ind = 0;
	int cnt = 0;
	while (cur_ind < n) {
		int y = cur_ind;
		while (y < n && a[cur_ind].X == a[y].X) {
			++y;
		}
		wh[cnt] = a[cur_ind].X;
		for (; cur_ind < y; ++cur_ind) {
			p[a[cur_ind].Y] = cnt;
		}
		++cnt;
	}
	SegmentTreeCmp<ll> tree(cnt, greater<ll>(), 0);
	tree.init();
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		int pr = p[i] - 1;
		ll cur_max;
		if (pr >= 0) {
			cur_max = tree.query(0, pr);
		}
		else {
			cur_max = 0;
		}
		ll new_max = cur_max + wh[p[i]];
		tree.update(p[i], new_max);
		umax(ans, new_max);
	}
	out << fixed << setprecision(16) << ans * PI << endl;
}
#include <fstream>


extern class IO io;
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


template<typename T>
T IO::read_number() {
	bool is_negative = false;
	while (!eof_ && !is_digit(current_char_) && (std::is_unsigned<T>() || current_char_ != '-')) {
		shift_char();
	}
	if (std::is_signed<T>() && current_char_ == '-') {
		is_negative = true;
		shift_char();
	}
	T result = 0;
	while (!eof_ && is_digit(current_char_)) {
		result = (result << 3) + (result << 1) + current_char_ - '0';
		shift_char();
	}
	return (is_negative ? result * -1 : result);
}


inline void IO::update_buffer() {
	if (read_buffer_offset_ == read_bytes_count_) {
		read_bytes_count_ = fread(&read_buffer_[0], sizeof(read_buffer_[0]), read_buffer_.size(), stdin);
		if (read_bytes_count_ == 0) {
			eof_ = true;
			return;
		}
		read_buffer_offset_ = 0;
	}
}

inline void IO::shift_char() {
	update_buffer();
	current_char_ = read_buffer_[read_buffer_offset_++];
}

inline int32_t IO::next_int() {
	return read_number<int32_t>();
}


inline int64_t IO::next_long()  {
	return read_number<int64_t>();
}


IO& IO::operator >>(int32_t& x) {
	x = ::next_int();
	return *this;
}


IO& IO::operator >>(int64_t& x) {
	x = ::next_long();
	return *this;
}


inline void IO::flush() {
	fwrite(&write_buffer_[0], sizeof(write_buffer_[0]), write_buffer_offset_, stdout);
	write_buffer_offset_ = 0;
}


inline int32_t next_int() {
	if (useFastIO) {
		return io.next_int();
	}
	int32_t ret;
	*pin >> ret;
	return ret;
}


inline int64_t next_long() {
	if (useFastIO) {
		return io.next_long();
	}
	int64_t ret;
	*pin >> ret;
	return ret;
}

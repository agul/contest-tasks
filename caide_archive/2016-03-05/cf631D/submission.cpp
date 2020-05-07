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

#define X first
#define Y second
#define all(a) a.begin(), a.end()

#define ll int64_t
#define pli std::pair<ll, int>

const int INF = 0x3f3f3f3f;


namespace std {


}

#ifdef _MSC_VER

#endif


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
	inline void skipws();

	inline int32_t next_int();
	inline char next_char();

	IO& operator >>(int32_t& x);
	IO& operator >>(char& x);

	inline void flush();
	inline void new_line();

	inline void print_long(const int64_t x);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const int64_t x);

	// Intended to use with std::endl.
	IO& operator <<(std::ostream& (*)(std::ostream&));


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

	template<typename T>
	void print_number(const T& value);

};

extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;
extern IO io;

inline int32_t next_int();


inline char next_char();

inline void new_line();

inline void print_long(const int64_t x);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;

IO io;


void parse_string(vector<pli>& a, int n) {
	for (int i = 0; i < n; ++i) {
		int x;
		io >> x;
		char ch;
		io >> ch >> ch;
		if (!a.empty() && a.back().Y == ch) {
			a.back().X += x;
		}
		else {
			a.emplace_back(x, ch);
		}
	}
}

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	vector<pli> a, b;
	parse_string(a, n);
	parse_string(b, m);
	n = a.size();
	m = b.size();
	ll ans = 0;
	if (m > 2) {
		vector<pli> c;
		copy(b.begin() + 1, b.begin() + m - 1, back_inserter(c));
		c.emplace_back(INF, INF);
		copy(all(a), back_inserter(c));
		int len = n + m - 1;
		vector<int> p(len);
		p[0] = 0;
		for (int i = 1; i < len; ++i) {
			int j = p[i - 1];
			while (j > 0 && c[i] != c[j]) {
				j = p[j - 1];
			}
			if (c[i] == c[j]) {
				++j;
			}
			p[i] = j;
		}
		for (int i = m; i < len - 1; ++i) {
			if (p[i] == m - 2 && a[i - m + 1 - m + 2].Y == b[0].Y && a[i - m + 1 - m + 2].X >= b[0].X && a[i - m + 1 + 1].Y == b[m - 1].Y && a[i - m + 1 + 1].X >= b[m - 1].X) {
				++ans;
			}
		}
	} else
	if (m == 2) {
		for (int i = 0; i < n - 1; ++i) {
			if (a[i].Y == b[0].Y && a[i + 1].Y == b[1].Y && a[i].X >= b[0].X && a[i + 1].X >= b[1].X) {
				++ans;
			}
		}
	}
	else {
		for (int i = 0; i < n; ++i) {
			if (a[i].Y == b[0].Y) {
				ans += max(0LL, a[i].X - b[0].X + 1);
			}
		}
	}
	io << ans << endl;
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


inline void IO::skipws() {
	while (!eof_ && (current_char_ == ' ' || current_char_ == '\n')) {
		shift_char();
	}
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

template<typename T>
void IO::print_number(const T& value) {
	T current_value = value;
	if (write_buffer_offset_ + 32 > kBufferSize) {
		flush();
	}
	if (current_value < 0) {
		write_buffer_[write_buffer_offset_++] = '-';
		current_value = abs(current_value);
	} else
	if (current_value == 0) {
		write_buffer_[write_buffer_offset_++] = '0';
		return;
	}
	std::size_t start_index = write_buffer_offset_;
	while (current_value != 0) {
		write_buffer_[write_buffer_offset_++] = current_value % 10 + '0';
		current_value /= 10;
	}
	std::reverse(write_buffer_.begin() + start_index, write_buffer_.begin() + write_buffer_offset_);
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


inline char IO::next_char() {
	if (current_char_ == '\0') {
		shift_char();
	}
	skipws();
	char ret = current_char_;
	shift_char();
	return ret;
}


IO& IO::operator >>(int32_t& x) {
	x = ::next_int();
	return *this;
}


IO& IO::operator >>(char& x) {
	x = ::next_char();
	return *this;
}


inline void IO::flush() {
	fwrite(&write_buffer_[0], sizeof(write_buffer_[0]), write_buffer_offset_, stdout);
	write_buffer_offset_ = 0;
}

inline void IO::new_line() {
	if (write_buffer_offset_ == kBufferSize) {
		flush();
	}
	write_buffer_[write_buffer_offset_++] = '\n';
}


inline void IO::print_long(const int64_t x) {
	print_number(x);
}


IO& IO::operator <<(const int64_t x) {
	::print_long(x);
	return *this;
}


IO& IO::operator <<(std::ostream& (*)(std::ostream&)) {
	::new_line();
	return *this;
}

inline int32_t next_int() {
	if (useFastIO) {
		return io.next_int();
	}
	int32_t ret;
	*pin >> ret;
	return ret;
}


inline char next_char() {
	if (useFastIO) {
		return io.next_char();
	}
	char ch;
	*pin >> std::skipws >> ch;
	return ch;
}


inline void new_line() {
	if (useFastIO) {
		io.new_line();
		return;
	}
	*pout << std::endl;
}


inline void print_long(const int64_t x) {
	if (useFastIO) {
		io.print_long(x);
		return;
	}
	*pout << x;
}

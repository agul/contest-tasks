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


#define ll int64_t


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

	inline int32_t next_int();
	inline int64_t next_long();

	IO& operator >>(int32_t& x);
	IO& operator >>(int64_t& x);

	inline void flush();
	inline void new_line();

	inline void print_int(const int32_t x);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const int32_t x);

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
inline int64_t next_long();


inline void new_line();

inline void print_int(const int32_t x);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;

IO io;
const int MAXN = 111;

using Container = unordered_map<ll, int>;

ll need;
ll suf[MAXN], can[MAXN];

void solve(istream& ins, ostream& out) {
	int n;
	io >> n >> need;
	vector<ll> a(n);
	for (auto& it : a) {
		io >> it;
	}
	suf[n] = 0;
	can[n] = 1;
	for (int i = n - 1; i >= 0; --i) {
		suf[i] = suf[i + 1] + (a[i] == 1 ? 0 : a[i]);
		if (can[i + 1] < need) {
			can[i] = can[i + 1] * a[i];
		}
		else {
			can[i] = can[i + 1];
		}
	}
	vector<Container> num(n + 1);
	num[0][0] = 1;
	for (int i = 0; i < n; ++i) {
		for (const auto& it : num[i]) {
			ll cur_mul = 1;
			for (int j = i; j < n; ++j) {
				cur_mul *= a[j];
				if (cur_mul > need) {
					break;
				}
				ll cur_res = it.first + cur_mul;
				if (cur_res + suf[j + 1] > need || cur_res + can[j + 1] + n - j < need) {
					continue;
				}
				num[j + 1][cur_res] += it.second;
			}
		}
	}
	io << num[n][need] << endl;
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

inline void IO::new_line() {
	if (write_buffer_offset_ == kBufferSize) {
		flush();
	}
	write_buffer_[write_buffer_offset_++] = '\n';
}

inline void IO::print_int(const int32_t x) {
	print_number(x);
}


IO& IO::operator <<(const int32_t x) {
	::print_int(x);
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


inline int64_t next_long() {
	if (useFastIO) {
		return io.next_long();
	}
	int64_t ret;
	*pin >> ret;
	return ret;
}


inline void new_line() {
	if (useFastIO) {
		io.new_line();
		return;
	}
	*pout << std::endl;
}

inline void print_int(const int32_t x) {
	if (useFastIO) {
		io.print_int(x);
		return;
	}
	*pout << x;
}
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
#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#define fill(a, x) memset(a, x, sizeof(a))
#define X first

#define ll int64_t


template<class T> 
inline T& add_mod(T& a, const T& b, const T& mod = 1000000007) {
	if ((a += b) >= mod) {
		a -= mod;
	}
	return a;
}


template<class T>
inline T& mul_mod(T& a, const T& b, const T& mod = 1000000007) {
	a = a * b % mod;
	return a;
}


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

	IO& operator >>(int32_t& x);

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


inline void new_line();

inline void print_int(const int32_t x);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


#include "IO.h"


template<typename T>
class Matrix {
public:
	using RowStorage = std::vector<T>;
	using DataStorage = std::vector<RowStorage>;

	Matrix(const size_t rows_cnt, const size_t cols_cnt, const T mod = 1'000'000'007) :
		rows_cnt_(rows_cnt), cols_cnt_(cols_cnt),
		data_(rows_cnt, RowStorage(cols_cnt, 0)),
		mod_(mod) {}

	Matrix() = delete;


	RowStorage& operator[] (const size_t index) {
		return data_[index];
	}

	const RowStorage& operator[] (const size_t index) const {
		return data_[index];
	}

	size_t rows_cnt() const {
		return rows_cnt_;
	}

	size_t cols_cnt() const {
		return cols_cnt_;
	}

	Matrix operator * (const Matrix& rhs) const {
		Matrix result(rows_cnt_, rhs.cols_cnt_);
		for (size_t i = 0; i < rows_cnt_; i++) {
			for (size_t k = 0; k < rhs.cols_cnt_; k++) {
				for (size_t j = 0; j < rhs.rows_cnt_; j++) {
					add_mod(result[i][k], data_[i][j] * rhs[j][k] % mod_, mod_);
				}
			}
		}
		return result;
	}

	static Matrix identity_matrix(const size_t rows_cnt, const size_t cols_cnt) {
		Matrix result(rows_cnt, cols_cnt);
		for (size_t i = 0; i < std::min(rows_cnt, cols_cnt); ++i) {
			result[i][i] = 1;
		}
		return result;
	}

private:
	size_t rows_cnt_;
	size_t cols_cnt_;
	T mod_;

	DataStorage data_;

};


using namespace std;

IO io;
const int MAXM = 11111;
const int MAXK = 111;

int dp[MAXM][MAXK];

inline Matrix<ll> ppow(Matrix<ll> a, int b) {
	Matrix<ll> ret = Matrix<ll>::identity_matrix(a.rows_cnt(), a.cols_cnt());
	while (b) {
		if (b & 1) {
			ret = ret * a;
		}
		a = a * a;
		b >>= 1;
	}
	return ret;
}

int get_cnt(int x) {
	Matrix<ll> mt(4, 4);
	mt[0] = { 1, 1, 0, 0 };
	mt[1] = { 0, 1, 1, 0 };
	mt[2] = { 0, 0, 1, 1 };
	mt[3] = { 1,0,0,1 };
	return ppow(mt, x)[0][0];
}

void solve(istream& ins, ostream& out) {
	int n, k;
	io >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	fill(dp, 0);
	dp[0][0] = 1;
	for (int i = 0; i < n; ++i) {
		int cnt = get_cnt(a[i]);
		for (int j = 0; j <= k; ++j) {
			ll cur = dp[i][j];
			add_mod(dp[i + 1][j], static_cast<int>(cur));
			mul_mod(cur, (ll)cnt);
			add_mod(dp[i + 1][j + 1], (int)cur);
		}
	}
	io << dp[n][k] << endl;
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


IO& IO::operator >>(int32_t& x) {
	x = ::next_int();
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

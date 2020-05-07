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
#define all(a) a.begin(), a.end()


namespace std {


}

#ifdef _MSC_VER

#endif


inline uint32_t abs(const uint32_t x) {
	return x;
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

	IO& operator >>(int32_t& x);

	inline void flush();
	inline void new_line();

	inline void print_uint(const uint32_t x);
	inline void print_string(const char* s);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const uint32_t x);
	IO& operator <<(const std::string& s);

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

inline void print_uint(const uint32_t x);
inline void print_string(const char* s);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


template<typename T>
class Matrix {
public:
	using RowStorage = std::vector<T>;
	using DataStorage = std::vector<RowStorage>;

	Matrix(const size_t rows_cnt, const size_t cols_cnt, const T mod = 1000000007) :
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


private:
	size_t rows_cnt_;
	size_t cols_cnt_;
	T mod_;

	DataStorage data_;

};


using namespace std;

IO io;

constexpr int factorial(int n) {
	return n > 0 ? n * factorial(n - 1) : 1;
}

constexpr int fact[10] = {
	factorial(0),
	factorial(1),
	factorial(2),
	factorial(3),
	factorial(4),
	factorial(5),
	factorial(6),
	factorial(7),
	factorial(8),
	factorial(9)
};

inline int encode(const Matrix<int>& a) {
	int ret = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			ret = ret * 10 + a[i][j];
		}
	}
	return ret;
}

inline void decode(int val, Matrix<int>& a) {
	for (int i = 2; i >= 0; --i) {
		for (int j = 2; j >= 0; --j) {
			a[i][j] = val % 10;
			val /= 10;
		}
	}
}

int h, t, q[fact[9]][5];
unordered_set<int> used, happy;

void add(int x, int len, char dir, int val, int prev) {
	if (used.count(x)) {
		return;
	}
	used.insert(x);
	q[t][0] = x;
	q[t][1] = len;
	q[t][2] = dir;
	q[t][3] = val;
	q[t][4] = prev;
	++t;
}

void rotate_row(Matrix<int>& a, int row) {
	int tmp = a[row][0];
	a[row][0] = a[row][1];
	a[row][1] = a[row][2];
	a[row][2] = tmp;
}

void rotate_col(Matrix<int>& a, int col) {
	int tmp = a[0][col];
	a[0][col] = a[1][col];
	a[1][col] = a[2][col];
	a[2][col] = tmp;
}

void get_ans(int pos) {
	vector<string> ans;
	while (pos > 0) {
		string t = "";
		t += q[pos][2];
		t += to_string(q[pos][3]);
		ans.emplace_back(t);
		pos = q[pos][4];
	}
	reverse(all(ans));
	io << ans.size() << endl;
	for (const auto& it : ans) {
		io << it << endl;
	}
}

void solve(istream& ins, ostream& out) {
	Matrix<int> a(3, 3);
	happy = { 816357492, 618753294, 438951276, 276951438, 834159672, 492357816, 294753618, 672159834 };
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			io >> a[i][j];
		}
	}
	h = t = 0;
	used.clear();
	add(encode(a), 0, 0, 0, 0);
	while (h < t) {
		int cur_val = q[h][0];
		decode(cur_val, a);
		int cur_len = q[h][1];
		if (happy.count(cur_val)) {
			get_ans(h);
			return;
		}
		for (int i = 0; i < 3; ++i) {
			rotate_row(a, i);
			add(encode(a), cur_len + 1, 'L', i + 1, h);
			rotate_row(a, i);
			add(encode(a), cur_len + 1, 'R', i + 1, h);
			rotate_row(a, i);
			rotate_col(a, i);
			add(encode(a), cur_len + 1, 'U', i + 1, h);
			rotate_col(a, i);
			add(encode(a), cur_len + 1, 'D', i + 1, h);
			rotate_col(a, i);
		}
		++h;
	}
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


inline void IO::print_uint(const uint32_t x) {
	print_number(x);
}


inline void IO::print_string(const char* s) {
	for (std::size_t i = 0; s[i] != '\0'; ++i) {
		if (write_buffer_offset_ == kBufferSize) {
			flush();
		}
		write_buffer_[write_buffer_offset_++] = s[i];
	}
}


IO& IO::operator <<(const uint32_t x) {
	::print_uint(x);
	return *this;
}


IO& IO::operator <<(const std::string& s) {
	::print_string(s.c_str());
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


inline void print_uint(const uint32_t x) {
	if (useFastIO) {
		io.print_uint(x);
		return;
	}
	*pout << x;
}


inline void print_string(const char* s) {
	if (useFastIO) {
		io.print_string(s);
		return;
	}
	*pout << s;
}

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

#define fill(a, x) memset(a, x, sizeof(a))
#define all(a) a.begin(), a.end()


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
	inline void next_string(char* s);

	IO& operator >>(int32_t& x);
	IO& operator >>(char* s);

	inline void flush();
	inline void new_line();

	inline void print_char(const char ch);
	inline void print_string(const char* s);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const char x);
	IO& operator <<(const char* s);

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


};

extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;
extern IO io;

inline int32_t next_int();


inline void next_string(char* s);

inline void new_line();

inline void print_char(const char x);
inline void print_string(const char* s);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;

IO io;
const int MAXN = 111111;
const int MAXM = 55;

int get_num(char x) {
	if (x == 'I') {
		return 1;
	}
	if (x == 'V') {
		return 5;
	}
	if (x == 'X') {
		return 10;
	}
	if (x == 'L') {
		return 50;
	}
	if (x == 'C') {
		return 100;
	}
	if (x == 'D') {
		return 500;
	}
	if (x == 'M') {
		return 1000;
	}
	assert(false);
	return -1;
}

char rev_num(int x) {
	if (x == 1) {
		return 'I';
	}
	if (x == 5) {
		return 'V';
	}
	if (x == 10) {
		return 'X';
	}
	if (x == 50) {
		return 'L';
	}
	if (x == 100) {
		return 'C';
	}
	if (x == 500) {
		return 'D';
	}
	if (x == 1000) {
		return 'M';
	}
	assert(false);
	return -1;
}

bool dp[MAXM][MAXN];
char s[MAXN];

void relax(int x, int y) {
	if (y >= 0 && y <= 100000) {
		dp[x][y] = true;
	}
}

bool get(int x, int y) {
	if (y < 0 || y > 100000) {
		return false;
	}
	return dp[x][y];
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n >> s;
	int ls = strlen(s);
	vector<int> a(ls);
	for (int i = 0; i < ls; ++i) {
		a[i] = get_num(s[i]);
	}
	sort(all(a));
	int cur_ind = ls - 1;
	while (cur_ind >= 0 && a[cur_ind] == a.back()) {
		n -= a.back();
		--cur_ind;
	}
	fill(dp, false);
	dp[0][50000] = true;
	++cur_ind;
	for (int i = 0; i < cur_ind; ++i) {
		for (int j = 0; j < 100000; ++j) {
			if (!dp[i][j]) {
				continue;
			}
			relax(i + 1, j + a[i]);
			relax(i + 1, j - a[i]);
		}
	}
	n += 50000;
	if (!dp[cur_ind][n]) {
		io << "NO" << endl;
		return;
	}
	vector<char> plus, minus;
	int pos = cur_ind;
	while (pos > 0) {
		--pos;
		if (get(pos, n - a[pos])) {
			n -= a[pos];
			plus.emplace_back(rev_num(a[pos]));
		}
		else {
			n += a[pos];
			minus.emplace_back(rev_num(a[pos]));
		}
	}
	for (const auto& ch : minus) {
		io << ch;
	}
	for (int i = cur_ind; i < ls; ++i) {
		io << rev_num(a.back());
	}

	for (const auto& ch : plus) {
		io << ch;
	}
	io << endl;
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


inline void IO::next_string(char* s) {
	if (current_char_ == '\0') {
		shift_char();
	}
	skipws();
	std::size_t index = 0;
	while (!eof_ && current_char_ != ' ' && current_char_ != '\n') {
		s[index++] = current_char_;
		shift_char();
	}
	s[index] = 0;
}

IO& IO::operator >>(int32_t& x) {
	x = ::next_int();
	return *this;
}


IO& IO::operator >>(char* s) {
	::next_string(s);
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


inline void IO::print_char(const char x) {
	if (write_buffer_offset_ == kBufferSize) {
		flush();
	}
	write_buffer_[write_buffer_offset_++] = x;
}

inline void IO::print_string(const char* s) {
	for (std::size_t i = 0; s[i] != '\0'; ++i) {
		if (write_buffer_offset_ == kBufferSize) {
			flush();
		}
		write_buffer_[write_buffer_offset_++] = s[i];
	}
}


IO& IO::operator <<(const char x) {
	::print_char(x);
	return *this;
}

IO& IO::operator <<(const char* s) {
	::print_string(s);
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


inline void next_string(char* s) {
	if (useFastIO) {
		io.next_string(s);
		return;
	}
	*pin >> s;
}


inline void new_line() {
	if (useFastIO) {
		io.new_line();
		return;
	}
	*pout << std::endl;
}


inline void print_char(const char x) {
	if (useFastIO) {
		io.print_char(x);
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

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


#define ll int64_t


namespace std {


}

#ifdef _MSC_VER

#endif


namespace Random {


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

	inline void next_string(char* s);

	IO& operator >>(char* s);

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
	void print_number(const T& value);

};

extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;
extern IO io;


inline void next_string(char* s);

inline void new_line();

inline void print_long(const int64_t x);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;

IO io;
const int MAXN = 1111111;

char s[MAXN];

void solve(istream& ins, ostream& out) {
	io >> s;
	int ls = strlen(s);
	int cur_ind = 0;
	vector<int> groups;
	vector<char> val;
	while (cur_ind < ls) {
		int y = cur_ind;
		while (y < ls && s[y] == s[cur_ind]) {
			++y;
		}
		groups.emplace_back(y - cur_ind);
		val.emplace_back(s[cur_ind]);
		cur_ind = y;
	}
	ll ans = groups.size();
	ans *= (ans - 1);
	ans >>= 1;
	int cur = 0;
	for (const auto& it : groups) {
		if (it > 1) {
			++ans;
		}
		else
			if (cur > 0 && cur < val.size() - 1 && val[cur - 1] == val[cur + 1]) {
				--ans;
			}
		++cur;
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


inline void print_long(const int64_t x) {
	if (useFastIO) {
		io.print_long(x);
		return;
	}
	*pout << x;
}

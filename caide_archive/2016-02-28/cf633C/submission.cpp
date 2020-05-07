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

#define ll int64_t
#define pli std::pair<ll, int>


namespace std {

	template<typename T, typename U>
	struct hash<std::pair<T, U>> {
		std::size_t operator()(const std::pair<T, U>& lhs) const {
			return lhs.first * 877117 + lhs.second;
		}
	};

}

#ifdef _MSC_VER

#endif


namespace Random {


}


inline char lowerCase(const char ch) {
	return (ch >= 'A' && ch <= 'Z') ? ch ^ 32 : ch;
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


class StringView {
public:
	using iterator = const char*;

	constexpr StringView() : data_(nullptr), length_(0) {}
	constexpr StringView(const StringView&) = default;

	StringView(const char* data, size_t length) : data_(data), length_(length) {}

	constexpr char operator[](const size_t index) const {
		return data_[index];
	}


	constexpr size_t length() const {
		return length_;
	}


private:
	const char* data_;
	size_t length_;
};


class DoubleHasher_t {
public:
	static const uint32_t MA = static_cast<uint32_t>(1e9) + 7;
	static const uint32_t MB = static_cast<uint32_t>(1e9) + 9;

	int a, b;

	DoubleHasher_t() {}
	DoubleHasher_t(const int x) : a(x), b(x) {}
	DoubleHasher_t(const int a, const int b) : a(a), b(b) {}

	DoubleHasher_t operator + (const DoubleHasher_t &x) const {
		return DoubleHasher_t((a + x.a) % MA, (b + x.b) % MB);
	}

	DoubleHasher_t operator - (const DoubleHasher_t &x) const {
		return DoubleHasher_t((a + MA - x.a) % MA, (b + MB - x.b) % MB);
	}

	DoubleHasher_t operator * (const int x) const {
		return DoubleHasher_t(((ll)a * x) % MA, ((ll)b * x) % MB);
	}

	DoubleHasher_t operator * (const DoubleHasher_t &x) const {
		return DoubleHasher_t(((ll)a * x.a) % MA, ((ll)b * x.b) % MB);
	}


	explicit operator ll() const {
		return (ll)a * MB + b + 1;
	}

};

template<class T> class Hasher {
public:

	T * deg, * hash;
	int P;
	StringView str;

	Hasher(const int n, const int P = std::max(rand(), 307)) : P(P) {
		hash = new T[n + 1];
		deg = new T[n + 1];
		deg[0] = 1;
		for (int i = 1; i <= n; ++i) {
			deg[i] = deg[i - 1] * P;
		}
	}

	~Hasher() {
		delete[] hash;
		delete[] deg;
	}

	void hashString(const StringView& s) {
		str = s;
		hash[0] = 0;
		for (int i = 0; i < s.length(); ++i) {
			hash[i + 1] = hash[i] * P + s[i];
		}
	}

	T getHash(const int l, const int r) const {
		return hash[r] - hash[l - 1] * deg[r - l + 1];
	}


private:


};

using namespace std;

IO io;
const int MAXN = 11111;
const int MAXM = 111111;

int dp[MAXN];
char s[MAXN], t[MAXN];
string a[MAXM];
Hasher<DoubleHasher_t> hasher(MAXN);
unordered_map<pli, int> str;

void solve(istream& ins, ostream& out) {
	srand(time(nullptr));
	int ls;
	io >> ls >> s;
	reverse(s, s + ls);
	for (int i = 0; i < ls; ++i) {
		s[i] = lowerCase(s[i]);
	}
	int n;
	io >> n;
	str.clear();
	for (int i = 1; i <= n; ++i) {
		io >> t;
		int lt = strlen(t);
		a[i] = string(t, t + lt);
		for (int j = 0; j < lt; ++j) {
			t[j] = lowerCase(t[j]);
		}
		hasher.hashString(StringView(t, lt));
		ll cur_hash = static_cast<ll>(hasher.getHash(1, lt));
		str[{cur_hash, lt}] = i;
	}
	hasher.hashString(StringView(s, ls));
	fill(dp, -1);
	dp[0] = 0;
	for (int i = 1; i <= ls; ++i) {
		for (int j = max(0, i - 1000); j < i; ++j) {
			if (dp[j] == -1) {
				continue;
			}
			ll cur_hash = static_cast<ll>(hasher.getHash(j + 1, i));
			pli cur_pair = { cur_hash, i - j };
			if (str.count(cur_pair)) {
				dp[i] = str[cur_pair];
				break;
			}
		}
	}
	vector<int> ans;
	int cur_index = ls;
	while (cur_index > 0) {
		int cur_str = dp[cur_index];
		ans.emplace_back(cur_str);
		cur_index -= a[cur_str].length();
	}
	for (const auto& it : ans) {
		io << a[it] << ' ';
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

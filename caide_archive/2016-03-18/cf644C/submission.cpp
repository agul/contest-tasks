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

#define all(a) a.begin(), a.end()

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

	IO& operator >>(int32_t& x);

	inline void flush();
	inline void new_line();

	inline void print_int(const int32_t x);
	inline void print_char(const char ch);
	inline void print_string(const char* s);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const int32_t x);
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
inline void print_char(const char x);
inline void print_string(const char* s);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


class StringView {
public:
	using iterator = const char*;

	constexpr StringView() : data_(nullptr), length_(0) {}

	constexpr StringView(const StringView&) = default;
	constexpr StringView(StringView&&) = default;
	StringView& operator =(const StringView&) = default;
	StringView& operator =(StringView&&) = default;

	StringView(const std::string& data) : data_(data.c_str()), length_(data.length()) {}

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

	template<typename U>
	void hash_vector(const std::vector<U>& vec) {
		hash[0] = 0;
		for (int i = 0; i < vec.size(); ++i) {
			hash[i + 1] = hash[i] * P + vec[i];
		}
	}

	T getHash(const int l, const int r) const {
		return hash[r] - hash[l - 1] * deg[r - l + 1];
	}


private:


};


namespace oaht
{

	using std::size_t;

	enum class node_state {
		FREE,
		IN_USE,
		ERASED
	};


}


using namespace std;

IO io;
const int MAXN = 111111;

void parse_url(const string& url, string& host, string& path) {
	host = "";
	path = "";
	int slash_cnt = 0;
	for (const auto& ch : url) {
		if (ch == '/') {
			++slash_cnt;
		}
		if (slash_cnt < 3) {
			host += ch;
		}
		else {
			path += ch;
		}
	}
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<string> a(n);
	for (auto& it : a) {
		ins >> it;
	}
	sort(all(a));
	a.resize(unique(all(a)) - a.begin());
	n = a.size();
	vector<string> host;
	vector<ll> path;
	host.reserve(n);
	path.reserve(n);
	Hasher<DoubleHasher_t> hasher(32);
	for (const auto& it : a) {
		string cur_host, cur_path;
		parse_url(it, cur_host, cur_path);
		host.emplace_back(cur_host);
		hasher.hashString(cur_path);
		path.emplace_back(static_cast<ll>(hasher.getHash(1, cur_path.length())));
	}
	Hasher<DoubleHasher_t> hasher_vec(MAXN);
	int cur_ind = 0;
	unordered_map<ll, vector<string>> urls;
	while (cur_ind < n) {
		int y = cur_ind;
		vector<ll> paths;
		while (y < n && host[cur_ind] == host[y]) {
			paths.emplace_back(path[y]);
			++y;
		}
		hasher_vec.hash_vector(paths);
		urls[static_cast<ll>(hasher_vec.getHash(1, paths.size()))].emplace_back(host[cur_ind]);
		cur_ind = y;
	}
	int ans = 0;
	for (const auto& it : urls) {
		if (it.second.size() > 1) {
			++ans;
		}
	}
	io << ans << endl;
	for (const auto& vec : urls) {
		if (vec.second.size() == 1) {
			continue;
		}
		for (const auto& it : vec.second) {
			io << it << ' ';
		}
		io << endl;
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

inline void IO::print_int(const int32_t x) {
	print_number(x);
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


IO& IO::operator <<(const int32_t x) {
	::print_int(x);
	return *this;
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

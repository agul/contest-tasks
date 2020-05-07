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

	inline void print_long(const int64_t x);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const int64_t x);

	// Intended to use with std::endl.
	IO& operator <<(std::ostream& (*)(std::ostream&));

	static void assign_files(const std::string& task);

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

inline void print_long(const int64_t x);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;

IO io;
const int MAXN = 2048;

struct Item {
	int len;
	int x, y, align;
	Item() {}

	Item(int len, int x, int y) : len(len), x(x), y(y) {}

	void set(int _len, int _x, int _y) {
		len = _len;
		x = _x;
		y = _y;
	}

	bool operator < (const Item& rhs) const {
		return len < rhs.len;
	}
};

int a[MAXN], b[MAXN], p[MAXN * MAXN];
Item edges[MAXN * MAXN * 2];
ll ans;

int findSet(const int v) {
	if (v == p[v]) {
		return v;
	}
	return p[v] = findSet(p[v]);
}

void unite(int a, int b, int len) {
	a = findSet(a), b = findSet(b);
	if (a == b) {
		return;
	}
	if (rand() & 1) {
		std::swap(a, b);
	}
	ans += len;
	p[a] = b;
}

void solve(istream& ins, ostream& out) {
	srand(time(NULL));
	IO::assign_files("fencedin");
	int n, m, A, B;
	io >> A >> B >> n >> m;
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	for (int i = 0; i < m; ++i) {
		io >> b[i];
	}
	a[n] = 0;
	b[m] = 0;
	a[n + 1] = A;
	b[m + 1] = B;
	sort(a, a + n + 2);
	sort(b, b + m + 2);
	int cnt = 0;
	int cur_id = 0;
	for (int j = 1; j <= m + 1; ++j) {
		int diff = b[j] - b[j - 1];
		for (int i = 1; i <= n; ++i, ++cur_id) {
			edges[cnt++] = {diff, cur_id, cur_id + 1};
		}
		++cur_id;
	}
	for (int i = 1; i <= n + 1; ++i) {
		cur_id = i - 1;
		int diff = a[i] - a[i - 1];
		for (int j = 1; j <= m; ++j, cur_id += n + 1) {
			edges[cnt++] = {diff, cur_id, cur_id + n + 1};
		}
	}
	sort(edges, edges + cnt);
	const int V = (n + 1) * (m + 1);
	for (int i = 0; i < V; ++i) {
		p[i] = i;
	}
	ans = 0;
	for (int i = 0; i < cnt; ++i) {
		auto& edge = edges[i];
		unite(edge.x, edge.y, edge.len);
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


void IO::assign_files(const std::string& task) {
	if (useFastIO) {
		freopen((task + ".in").c_str(), "r", stdin);
		freopen((task + ".out").c_str(), "w", stdout);
	}
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

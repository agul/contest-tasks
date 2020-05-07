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


const ll LINF = 0x3f3f3f3f3f3f3f3fLL;


template<class T> 
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}


#ifdef _MSC_VER


#endif


template<class T> inline T sqr(const T& x) {
	return x * x;
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


using namespace std;


IO io;


template<typename T>
class Point {
public:

	Point() : Point(0, 0) {}
	Point(const T x, const T y) : x_(x), y_(y) {}

	
	void read() {
		io >> x_ >> y_;
	}

	T sqr_dist(const Point& rhs) const {
		return sqr(x_ - rhs.x_) + sqr(y_ - rhs.y_);
	}

	double dist(const Point& rhs) const {
		return sqrt(sqr_dist(rhs));
	}

private:
	T x_;
	T y_;

};

void solve(istream& ins, ostream& out) {
	Point<ll> a, b, t;
	a.read();
	b.read();
	t.read();
	int n;
	io >> n;
	vector<Point<ll>> p(n);
	using pdi = std::pair<double, int>;
	vector<pdi> da(n), db(n);
	vector<double> dt(n);
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		auto& it = p[i];
		it.read();
		double to_trash = it.dist(t);
		dt[i] = to_trash;
		da[i] = { to_trash - it.dist(a), i };
		db[i] = { to_trash - it.dist(b), i };
		sum += to_trash;
	}
	out << fixed << setprecision(16);
	sort(all(da), greater<pdi>());
	sort(all(db), greater<pdi>());
	double ans = LINF;
	if (n > 1) {
		if (da[0].second == db[0].second) {
			double x = da[0].first + db[1].first;
			double y = da[1].first + db[0].first;
			{
				double dist_from_a = p[da[0].second].dist(a);
				double dist_from_b = p[db[1].second].dist(b);
				double to_trash_sum = dt[da[0].second] + dt[db[1].second];
				umin(ans, dist_from_a + dist_from_b + 2 * sum - to_trash_sum);
			}
			{
				double dist_from_a = p[da[1].second].dist(a);
				double dist_from_b = p[db[0].second].dist(b);
				double to_trash_sum = dt[da[1].second] + dt[db[0].second];
				umin(ans, dist_from_a + dist_from_b + 2 * sum - to_trash_sum);
			}
		}
		else {
			double dist_from_a = p[da[0].second].dist(a);
			double dist_from_b = p[db[0].second].dist(b);
			double to_trash_sum = dt[da[0].second] + dt[db[0].second];
			umin(ans, dist_from_a + dist_from_b + 2 * sum - to_trash_sum);
		}
	}
	{
		double dist_from_a = p[da[0].second].dist(a);
		double to_trash = dt[da[0].second];
		umin(ans, dist_from_a + 2 * sum - to_trash);
	}
	{
		double dist_from_b = p[db[0].second].dist(b);
		double to_trash = dt[db[0].second];
		umin(ans, dist_from_b + 2 * sum - to_trash);
	}
	out << ans << endl;
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



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

#define X first
#define Y second


#define pii std::pair<int, int>


const int INF = 0x3f3f3f3f;


const int DX[] = { -1, 0, 1, 0, -1, -1, 1, 1};
const int DY[] = { 0, 1, 0, -1, -1, 1, 1, -1};

enum class Direction {
	Up,
	Right,
	Down,
	Left,
	UpLeft,
	UpRight,
	DownRight,
	DownLeft,
	North = Up,
	East = Right,
	South = Down,
	West = Left,
	NorthWest = UpLeft,
	NorthEast = UpRight,
	SouthEast = DownRight,
	SouthWest = DownLeft
};


template<class T> 
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}


#ifdef _MSC_VER


#endif


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


inline void next_string(char* s);


inline void new_line();

inline void print_int(const int32_t x);


//inline void print_string(const std::string& s);

//inline void print_line(const std::string& s);


template<typename T>
class Queue {
public:
	using value_type = T;
	using size_type = size_t;
	
	
	using rvalue = value_type&&;
	using container = std::vector<value_type>;

	Queue(const size_type max_size) : data_(container(max_size)) {
		clear();
	}

	Queue() = delete;

	Queue(const Queue&) = default;
	Queue& operator =(const Queue&) = default;
	Queue(Queue&&) = default;
	Queue& operator =(Queue&&) = default;

	
	constexpr bool empty() const {
		return head_index_ == tail_index_;
	}

	void clear() {
		head_index_ = 0;
		tail_index_ = 0;
	}

	
	void push(rvalue value) {
		data_[tail_index_++] = std::move(value);
	}

	value_type pop_front() {
		return data_[head_index_++];
	}

	
	/* bool operator ==(const Queue& rhs) const {
	return top_index_ == rhs.top_index_ && data_ == rhs.data_;
	}

	bool operator !=(const Queue& rhs) const {
	return !operator==(rhs);
	}

	bool operator <(const Queue& rhs) const {
	return data_ < rhs.data_;
	}

	bool operator <=(const Queue& rhs) const {
	return data_ <= rhs.data_;
	}

	bool operator >(const Queue& rhs) const {
	return data_ > rhs.data_;
	}

	bool operator >=(const Queue& rhs) const {
	return data_ >= rhs.data_;
	} */

private:
	container data_;
	size_type head_index_;
	size_type tail_index_;

};


using namespace std;


IO io;

const int MAXN = 1111;

class Cell {
public:
	Cell() : Cell('*') {}

	Cell(const bool up, const bool right, const bool down, const bool left) {
		set(up, right, down, left);
	}

	Cell(const char ch) {
		if (ch == '+') {
			set(1, 1, 1, 1);
		} else
		if (ch == '-') {
			set(0, 1, 0, 1);
		} else
		if (ch == '|') {
			set(1, 0, 1, 0);
		} else
		if (ch == '^') {
			set(1, 0, 0, 0);
		} else
		if (ch == '>') {
			set(0, 1, 0, 0);
		} else
		if (ch == 'v') {
			set(0, 0, 1, 0);
		} else
		if (ch == '<') {
			set(0, 0, 0, 1);
		} else
		if (ch == 'L') {
			set(1, 1, 1, 0);
		} else
		if (ch == 'R') {
			set(1, 0, 1, 1);
		} else
		if (ch == 'U') {
			set(0, 1, 1, 1);
		} else
		if (ch == 'D') {
			set(1, 1, 0, 1);
		} else
		if (ch == '*') {
			set(0, 0, 0, 0);
		}
		else {
			assert(false);
		}
	}

	bool left() const {
		return left_;
	}

	bool right() const {
		return right_;
	}

	bool up() const {
		return up_;
	}

	bool down() const {
		return down_;
	}

	Cell rotate() const {
		return{ left_, up_, right_, down_ };
	}

private:
	bool up_;
	bool right_;
	bool down_;
	bool left_;

	void set(const bool up, const bool right, const bool down, const bool left) {
		up_ = up;
		right_ = right;
		down_ = down;
		left_ = left;
	}

};

class Point3D {
public:
	Point3D() : Point3D(0, 0, 0) {}
	Point3D(const int x, const int y, const int z) :
		x_(x), y_(y), z_(z) {}
	
	int x() const {
		return x_;
	}

	int y() const {
		return y_;
	}

	int z() const {
		return z_;
	}

private:
	int x_;
	int y_;
	int z_;

};

Queue<Point3D> q(MAXN * MAXN * 4);
Cell field[4][MAXN][MAXN];
int dist[4][MAXN][MAXN];
char row[MAXN];
bool used[4][MAXN][MAXN];
int n, m;

inline bool check_bounds(const int z, const int x, const int y) {
	return x > 0 && x <= n && y > 0 && y <= m && z >= 0 && z < 4;
}

inline void add(const int z, const int x, const int y, const int len) {
	if (check_bounds(z, x, y) && !used[z][x][y]) {
		dist[z][x][y] = len;
		used[z][x][y] = true;
		q.push({ x, y, z });
	}
}

bool connection(const Cell& lhs, const Cell& rhs, const Direction dir) {
	if (dir == Direction::Up) {
		return lhs.up() && rhs.down();
	}
	if (dir == Direction::Right) {
		return lhs.right() && rhs.left();
	}
	if (dir == Direction::Down) {
		return lhs.down() && rhs.up();
	}
	if (dir == Direction::Left) {
		return lhs.left() && rhs.right();
	}
	assert(false);
	return false;
}

void solve(istream& ins, ostream& out) {
	io >> n >> m;
	for (int i = 1; i <= n; ++i) {
		io >> row;
		for (int j = 1; j <= m; ++j) {
			field[0][i][j] = Cell(row[j - 1]);
			for (int k = 1; k < 4; ++k) {
				field[k][i][j] = field[k - 1][i][j].rotate();
			}
		}
	}
	pii start, finish;
	io >> start.X >> start.Y >> finish.X >> finish.Y;
	fill(dist, INF);
	add(0, start.X, start.Y, 0);
	while (!q.empty()) {
		const auto point = q.pop_front();
		const int len = dist[point.z()][point.x()][point.y()];
		const Cell& cur = field[point.z()][point.x()][point.y()];
		for (int dir = 0; dir < 4; ++dir) {
			const int new_z = point.z();
			const int new_x = point.x() + DX[dir];
			const int new_y = point.y() + DY[dir];
			if (!check_bounds(new_z, new_x, new_y)) {
				continue;
			}
			const Cell& rhs = field[new_z][new_x][new_y];
			if (connection(cur, rhs, static_cast<Direction>(dir))) {
				add(new_z, new_x, new_y, len + 1);
			}
		}
		add((point.z() + 1) & 3, point.x(), point.y(), len + 1);
	}
	int ans = INF;
	for (int i = 0; i < 4; ++i) {
		umin(ans, dist[i][finish.X][finish.Y]);
	}
	io << (ans == INF ? -1 : ans) << endl;
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

inline void print_int(const int32_t x) {
	if (useFastIO) {
		io.print_int(x);
		return;
	}
	*pout << x;
}



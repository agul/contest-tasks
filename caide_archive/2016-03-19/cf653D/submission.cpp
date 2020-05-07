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

const double EPS = 1e-9;


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


//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;

IO io;

template <typename FlowSize>
class DinicFlow {
	struct Edge {
		std::size_t from, to;
		FlowSize cap;
		FlowSize flow;
	};
public:
	DinicFlow(std::size_t n) : g(n), queue(n), pointer(n), used(n), d(n) {
	}

	void addEdge(std::size_t from, std::size_t to, FlowSize capacity) {
		return addTwoSidedEdge(from, to, capacity, 0);
	}

	void addTwoSidedEdge(std::size_t from, std::size_t to, FlowSize capacity, FlowSize backwardCapacity) {
		Edge edge = { from, to, capacity, 0 };
		g[from].push_back(edges.size());
		edges.push_back(edge);

		Edge backwardEdge = { to, from, backwardCapacity, 0 };
		g[to].push_back(edges.size());
		edges.push_back(backwardEdge);
	}


	FlowSize findFlow(std::size_t from, std::size_t to, FlowSize infinity = std::numeric_limits<FlowSize>::max()) {
		FlowSize flow = 0;
		while (bfs(from, to)) {
			memset(&pointer[0], 0, sizeof(std::size_t) * pointer.size());
			while (FlowSize pushed = dfs(from, to, infinity)) {
				flow += pushed;
			}
		}
		return flow;
	}


private:

	bool bfs(std::size_t from, std::size_t to) {
		memset(&used[0], false, sizeof(char) * used.size());
		std::size_t qh = 0, qt = 0;
		queue[qt++] = from;
		used[from] = true;
		while (qh != qt) {
			std::size_t v = queue[qh++];
			for (std::size_t id : g[v]) {
				Edge& edge = edges[id];
				if (used[edge.to]) {
					continue;
				}
				if (edge.cap == edge.flow) {
					continue;
				}
				used[edge.to] = true;
				d[edge.to] = d[v] + 1;
				queue[qt++] = edge.to;
			}
		}
		return used[to];
	}

	FlowSize dfs(std::size_t v, std::size_t to, FlowSize mx) {
		if (mx == 0) {
			return 0;
		}

		if (v == to) {
			return mx;
		}

		for (std::size_t& i = pointer[v]; i < g[v].size(); ++i) {
			std::size_t id = g[v][i];
			Edge& e = edges[id];
			if (d[e.to] == d[v] + 1) {
				if (FlowSize pushed = dfs(e.to, to, std::min(mx, e.cap - e.flow))) {
					e.flow += pushed;
					edges[id ^ 1].flow -= pushed;
					return pushed;
				}
			}
		}
		return 0;
	}

	std::vector<std::vector<std::size_t>> g;
	std::vector<Edge> edges;

	/**
	* Variables for actual flow calculation.
	* TODO: consider moving them so that they are not stored when not needed
	*/
	std::vector<std::size_t> queue; //std::queue is to slow, not removing values is faster
	std::vector<std::size_t> pointer;
	std::vector<char> used;
	std::vector<FlowSize> d;
};

struct Edge {
	int from, to, cap;
	Edge() {}
	void read() {
		io >> from >> to >> cap;
		--from, --to;
	}
};

void solve(istream& ins, ostream& out) {
	int n, m, x;
	io >> n >> m >> x;
	vector<Edge> e(m);
	for (int i = 0; i < m; ++i) {
		e[i].read();
	}
	double L = 0, R = 1e6;
	for (int iter = 0; iter < 60; ++iter) {
		double md = (L + R) / 2;
		if (md < EPS) {
			break;
		}
		DinicFlow<ll> flow(n);
		for (int i = 0; i < m; ++i) {
			ll cap = static_cast<ll>(e[i].cap / md + EPS);
			flow.addEdge(e[i].from, e[i].to, cap);
		}
		ll flow_value = flow.findFlow(0, n - 1);
		(flow_value < x ? R : L) = md;
	}
	out << fixed << setprecision(16) << L * x << endl;
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


IO& IO::operator >>(int32_t& x) {
	x = ::next_int();
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

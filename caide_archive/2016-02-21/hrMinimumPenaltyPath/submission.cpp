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
#define sz(a) ((int)a.size())

#define ll int64_t
#define vi std::vector<int>
#define vvi std::vector<vi>


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


class Graph {
public:
	enum Type {
		GT_WEIGHTED = 1,
		GT_FLOW = 2
	};

	int *from, *to, *parent;
	ll *weight;
	vvi edges;
	int maxVertexNum, maxEdgesNum;
	int vertexCount, edgesCount;

	Graph(const int maxVertexNum, const int maxEdgesNum, const int mask = 0);

	virtual ~Graph() {
		deepClear();
	}


	void clear(int size = -1);
	void deepClear();

	int addDirectedEdge(const int _from, const int _to);
	int addDirectedWeightedEdge(const int _from, const int _to, const ll _weight);


private:

};

class UndirectedGraph : public Graph {
public:

	UndirectedGraph(const int maxVertexNum, const int maxEdgesNum, const int mask = 0) : Graph(maxVertexNum, maxEdgesNum << 1, mask) {}

	void initGraph(const int _vertexCount) {
		vertexCount = _vertexCount;
	}

	void addBidirectionalWeightedEdge(const int _from, const int _to, const ll _weight);

private:

};


using namespace std;

IO io;
const int MAXN = 1111;
const int MAXM = 11111;

int start, finish;
UndirectedGraph graph(MAXN, MAXM, Graph::GT_WEIGHTED);
bool used[MAXN];

bool dfs(int v, int cur_len, int max_len) {
	used[v] = true;
	for (const auto& it : graph.edges[v]) {
		int to = graph.to[it];
		int len = graph.weight[it];
		int new_len = cur_len | len;
		if (used[to] || (new_len | max_len) != max_len) {
			continue;
		}
		if (to == finish) {
			return true;
		}
		if (dfs(to, new_len, max_len)) {
			return true;
		}
	}
	return false;
}

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	graph.clear();
	graph.initGraph(n);
	for (int i = 0; i < m; ++i) {
		int from, to, len;
		io >> from >> to >> len;
		--from, --to;
		graph.addBidirectionalWeightedEdge(from, to, len);
	}
	io >> start >> finish;
	--start, --finish;
	for (int max_len = 1; max_len <= 1024; ++max_len) {
		fill(used, 0);
		if (dfs(start, 0, max_len)) {
			io << max_len << endl;
			return;
		}
	}
	io << -1 << endl;
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


Graph::Graph(const int maxVertexNum, const int maxEdgesNum, const int mask) : maxVertexNum(maxVertexNum), maxEdgesNum(maxEdgesNum) {
	from = new int[maxEdgesNum];
	to = new int[maxEdgesNum];
	edges.resize(maxVertexNum);
	weight = (mask & GT_WEIGHTED ? new ll[maxEdgesNum] : NULL);
	vertexCount = 0;
	edgesCount = 0;
}

void Graph::clear(int size) {
	edgesCount = 0;
	size = (size == -1 ? sz(edges) : std::min(size, sz(edges)));
	if (size == -1) {
		size = sz(edges);
	}
	for (int i = 0; i < size; ++i) {
		edges[i].clear();
	}
}

void Graph::deepClear() {
	maxVertexNum = 0;
	maxEdgesNum = 0;
	edgesCount = 0;
	edges.clear();
	if (from != NULL) {
		delete[] from;
	}
	if (to != NULL) {
		delete[] to;
	}
	if (weight != NULL) {
		delete[] weight;
	}
	if (parent != NULL) {
		delete[] parent;
	}
}

int Graph::addDirectedEdge(const int _from, const int _to) {
	from[edgesCount] = _from;
	to[edgesCount] = _to;
	edges[_from].emplace_back(edgesCount);
	return edgesCount++;
}

int Graph::addDirectedWeightedEdge(const int _from, const int _to, const ll _weight) {
	weight[edgesCount] = _weight;
	return addDirectedEdge(_from, _to);
}


void UndirectedGraph::addBidirectionalWeightedEdge(const int _from, const int _to, const ll _weight) {
	addDirectedWeightedEdge(_from, _to, _weight);
	addDirectedWeightedEdge(_to, _from, _weight);
}

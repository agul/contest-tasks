#ifdef __GNUC__
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
#endif
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
#define sz(a) ((int)a.size())
#define X first
#define Y second

#define all(a) a.begin(), a.end()


#define ll int64_t


#define pii std::pair<int, int>


#define vi std::vector<int>
#define vvi std::vector<vi>


template<class T> 
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

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

	static std::chrono::system_clock::rep GetRandSeed() {
		return std::chrono::system_clock::now().time_since_epoch().count();
	}

	
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
	
	//inline void print_string(const std::string& s);
	
	//inline void print_line(const std::string& s);

	IO& operator <<(const int32_t x);
	
	
	IO& operator <<(const char x);
	
	
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

	void initGraph(const int _vertexCount) {
		vertexCount = _vertexCount;
	}

	
	void clear(int size = -1);
	void deepClear();

	int addDirectedEdge(const int _from, const int _to);
	

	bool topSortAcyclic(int order[]) const;
	
	
private:
	
	
};


class DSU {
public:
	
	int * p, n, numSets;

	DSU(const int N) {
		p = new int[N];
	}

	~DSU() {
		delete[] p;
	}

	void init(const int _n);
	int findSet(const int v);
	bool unite(int a, int b);
	void finalize();

	size_t size() const {
		return n;
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

	template<typename _Key, typename _Value>
	struct node {
		_Key key;
		_Value value;
		node_state state = node_state::FREE;
	};

	template<typename _Key, typename _Value, typename _Hash = std::hash<_Key>>
	class hash_map {
	public:		
		const node<_Key, _Value> UNDEFINED;

		hash_map(size_t capacity) : capacity(capacity), size(0), UNDEFINED(node<_Key, _Value>()) {
			nodes = new node<_Key, _Value>[capacity];

			for (size_t i = 0; i < capacity; i++)
				nodes[i] = node<_Key, _Value>();
		}

		hash_map() : hash_map(3) {
		}

		
		_Value& operator[](const _Key& key) {
			if ((size << 1) > capacity)
				rehash();

			size_t index;
			bool result = put(key, index, nodes, capacity);
			if (result)
				size++;

			return nodes[index].value;
		}

		void clear() {
			for (size_t d = 0; d < capacity; d++) {
				nodes[d].state = node_state::FREE;
			}
			size = 0;
		}

		~hash_map() {
			delete[] nodes;
		}

		size_t capacity;
		size_t size;

		node<_Key, _Value>* nodes;
		
	private:
		size_t get_index(const _Key& key, size_t size) const {
			return (h(key) * 22543) % size;
		}

		void rehash() {
			size_t n_capacity = (capacity << 1);

			node<_Key, _Value>* n_nodes = new node<_Key, _Value>[n_capacity];
			for (size_t i = 0; i < n_capacity; i++)
				n_nodes[i] = node<_Key, _Value>();

			for (size_t i = 0; i < capacity; i++)
			if (nodes[i].state == node_state::IN_USE) {
				size_t index;
				put(nodes[i].key, index, n_nodes, n_capacity);
				n_nodes[index].value = nodes[i].value;
			}

			delete[] nodes;

			nodes = n_nodes;
			capacity = n_capacity;
		}

		bool put(const _Key& key, size_t& index, node<_Key, _Value>* nodes, size_t nodes_length) {
			index = get_index(key, nodes_length);

			for (size_t i = 0; i < nodes_length; i++) {
				if (nodes[index].state == node_state::FREE
					|| nodes[index].state == node_state::ERASED) {
					nodes[index].key = key;
					nodes[index].state = node_state::IN_USE;
					nodes[index].value = 0;
					return true;
				}

				if (nodes[index].key == key)
					return false;

				index++;
				if (index == nodes_length)
					index = 0;
			}

			return false;
			// throw std::logic_error("Unexpected case.");
		}

		_Hash h;
	};

}


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

	
	typename DataStorage::iterator begin() {
		return data_.begin();
	}

	
	typename DataStorage::iterator end() {
		return data_.end();
	}

	
	RowStorage& operator[] (const size_t index) {
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

const int MAXN = 1111111;

int n, m, compressed[MAXN], order[MAXN], vals[MAXN];
DSU dsu(MAXN);
Graph inGraph(MAXN, MAXN * 2), graph(MAXN, MAXN * 2);
oaht::hash_map<pii, bool> edges;

void add_edge(int from, int to) {
	auto& it = edges[{from, to}];
	if (it) {
		return;
	}
	it = true;
	graph.addDirectedEdge(from, to);
}

inline int get_id(int x, int y) {
	return x * m + y;
}

void solve(istream& ins, ostream& out) {
	edges.clear();
	graph.clear();
	inGraph.clear();
	io >> n >> m;
	Matrix<int> a(n, m);
	for (auto& row : a) {
		for (auto& cell : row) {
			io >> cell;
		}
	}
	int vc = n * m;
	inGraph.initGraph(vc);
	dsu.init(vc);
	for (int i = 0; i < n; ++i) {
		vector<pii> row;
		row.reserve(m);
		for (int j = 0; j < m; ++j) {
			row.emplace_back(a[i][j], j);
		}
		sort(all(row));
		for (int j = 1; j < m; ++j) {
			int cur_vertex = get_id(i, row[j].Y);
			int prev_vertex = get_id(i, row[j - 1].Y);
			if (row[j].X == row[j - 1].X) {
				dsu.unite(prev_vertex, cur_vertex);
			}
			else {
				inGraph.addDirectedEdge(prev_vertex, cur_vertex);
			}
		}
	}
	for (int j = 0; j < m; ++j) {
		vector<pii> col;
		col.reserve(n);
		for (int i = 0; i < n; ++i) {
			col.emplace_back(a[i][j], i);
		}
		sort(all(col));
		for (int i = 1; i < n; ++i) {
			int cur_vertex = get_id(col[i].Y, j);
			int prev_vertex = get_id(col[i - 1].Y, j);
			if (col[i].X == col[i - 1].X) {
				dsu.unite(prev_vertex, cur_vertex);
			}
			else {
				inGraph.addDirectedEdge(prev_vertex, cur_vertex);
			}
		}
	}
	dsu.finalize();
	fill(compressed, -1);
	int cnt = 0;
	for (int i = 0; i < dsu.size(); ++i) {
		int v = dsu.p[i];
		if (compressed[v] == -1) {
			compressed[v] = cnt++;
		}
	}
	graph.initGraph(cnt);
	for (int i = 0; i < vc; ++i) {
		int cur_vertex = compressed[dsu.p[i]];
		for (const auto& it : inGraph.edges[i]) {
			int to = inGraph.to[it];
			int to_vertex = compressed[dsu.p[to]];
			add_edge(cur_vertex, to_vertex);
		}
	}
	graph.topSortAcyclic(order);
	fill(vals, 0);
	for (int i = 0; i < cnt; ++i) {
		int v = order[i];
		if (vals[v] == 0) {
			vals[v] = 1;
		}
		for (const auto& it : graph.edges[v]) {
			int to = graph.to[it];
			umax(vals[to], vals[v] + 1);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int id = get_id(i, j);
			int cur_set = dsu.p[id];
			int comp = compressed[cur_set];
			int val = vals[comp];
			io << val << ' ';
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


void DSU::init(const int _n) {
	n = _n;
	srand(static_cast<uint32_t>(Random::GetRandSeed()));
	std::iota(p, p + n, 0);
	numSets = n;
}

int DSU::findSet(const int v) {
	if (v == p[v]) {
		return v;
	}
	return p[v] = findSet(p[v]);
}

bool DSU::unite(int a, int b) {
	a = findSet(a), b = findSet(b);
	if (a == b) {
		return false;
	}
	if (rand() & 1) {
		std::swap(a, b);
	}
	p[a] = b;
	--numSets;
	return true;
}

void DSU::finalize() {
	for (int i = 0; i < n; ++i) {
		p[i] = findSet(p[i]);
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


IO& IO::operator <<(const int32_t x) {
	::print_int(x);
	return *this;
}


IO& IO::operator <<(const char x) {
	::print_char(x);
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


bool Graph::topSortAcyclic(int order[]) const 
// non-recursive topological sorting, works only for acyclic graphs 
{
	int * degree = new int[vertexCount];
	std::fill_n(degree, vertexCount, 0);
	for (int i = 0; i < edgesCount; ++i) {
		++degree[to[i]];
	}
	int head = 0, tail = 0;
	for (int i = 0; i < vertexCount; ++i) {
		if (!degree[i]) {
			order[tail++] = i;
		}
	}
	while (head < tail) {
		int curVertex = order[head++];
		for (auto& it : edges[curVertex]) {
			int toVertex = to[it];
			if (!(--degree[toVertex])) {
				order[tail++] = toVertex;
			}
		}
	}
	delete[] degree;
	return tail == vertexCount;
}



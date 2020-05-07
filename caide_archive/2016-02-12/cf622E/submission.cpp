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

using namespace std;

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

#define ll long long
#define pii pair<int, int>
#define vi vector<int>
#define vvi vector<vi>


template<class T> 
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

#ifdef _MSC_VER

#endif


inline bool isDigit(const char ch) {
	return (ch >= '0' && ch <= '9');
}


class IO {
public:

	static const int IO_ERR = -1;
	static const int BUFFER_SIZE = 1 << 18;
	
	bool eof;
	char curChar;

	IO() : rbCount(0), rbOffset(0), curChar(0), eof(false) {}

	~IO() {
		fwrite(writeBuffer, sizeof(writeBuffer[0]), wbOffset, stdout);
	}


	inline int nextInt();

	IO& operator >>(int& x);

	void newline();

	void printInt(int x);

	IO& operator <<(int x);
	IO& operator <<(ostream& (*fn)(ostream&));


private:
	char readBuffer[BUFFER_SIZE], writeBuffer[BUFFER_SIZE];
	size_t rbCount, rbOffset, wbOffset;

};

extern bool useFastIO;
extern istream * pin;
extern ostream * pout;
extern IO io;

inline int nextInt() {
	if (useFastIO) {
		return io.nextInt();
	}
	int ret;
	*pin >> ret;
	return ret;
}


inline void newline() {
	if (useFastIO) {
		io.newline();
		return;
	}
	*pout << endl;
}

inline void printInt(int x) {
	if (useFastIO) {
		io.printInt(x);
		return;
	}
	*pout << x;
}


namespace Random {


}


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


private:

};

class UndirectedGraph : public Graph {
public:

	UndirectedGraph(const int maxVertexNum, const int maxEdgesNum, const int mask = 0) : Graph(maxVertexNum, maxEdgesNum << 1, mask) {}

	void initGraph(const int _vertexCount) {
		vertexCount = _vertexCount;
	}

	void addBidirectionalEdge(const int _from, const int _to);

private:

};


IO io;
const int MAXN = 555555;

int parent[MAXN], depth[MAXN], col[MAXN], Tm[MAXN];
UndirectedGraph graph(MAXN, MAXN);
vector<pii> leaves;

void dfs(int v, int p, int lvl, int comp) {
	col[v] = comp;
	depth[v] = lvl;
	parent[v] = p;
	bool any = false;
	for (const auto& it : graph.edges[v]) {
		int to = graph.to[it];
		if (to == p) {
			continue;
		}
		any = true;
		dfs(to, v, lvl + 1, comp);
	}
	if (!any) {
		leaves.emplace_back(lvl, v);
	}
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	graph.clear();
	graph.initGraph(n);
	for (int i = 1; i < n; ++i) {
		int to, from;
		io >> from >> to;
		--to, --from;
		graph.addBidirectionalEdge(from, to);
	}
	fill(Tm, 0);
	int cnt = 0, ans = 0;
	for (const auto& it : graph.edges[0]) {
		int to = graph.to[it];
		leaves.clear();
		dfs(to, 0, 1, cnt++);
		sort(all(leaves));
		int prv = 0;
		for (const auto& leaf : leaves) {
			Tm[leaf.Y] = max(leaf.X, prv + 1);
			prv = Tm[leaf.Y];
		}
	}
	for (int i = 0; i < n; ++i) {
		umax(ans, Tm[i]);
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


inline int IO::nextInt() {
	while (!eof && !isDigit(curChar) && curChar != '-') {
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				return IO_ERR;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	bool neg = false;
	if (curChar == '-') {
		neg = true;
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				return IO_ERR;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	int result = 0;
	while (!eof && isDigit(curChar)) {
		result = (result << 3) + (result << 1) + curChar - '0';
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				return (neg ? -result : result);
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	return (neg ? -result : result);
}


IO& IO::operator >>(int& x) {
	x = ::nextInt();
	return *this;
}


void IO::newline() {
	if (wbOffset == BUFFER_SIZE) {
		// flush begin
		fwrite(writeBuffer, sizeof(writeBuffer[0]), wbOffset, stdout);
		wbOffset = 0;
		// flush end
	}
	writeBuffer[wbOffset++] = '\n';
}

void IO::printInt(int x) {
	if (wbOffset + 12 > BUFFER_SIZE) {
		// flush begin
		fwrite(writeBuffer, sizeof(writeBuffer[0]), wbOffset, stdout);
		wbOffset = 0;
		// flush end
	}
	if (x < 0) {
		writeBuffer[wbOffset++] = '-';
		x = -x;
	}
	else
	if (!x) {
		writeBuffer[wbOffset++] = '0';
		return;
	}
	int st = wbOffset;
	while (x) {
		writeBuffer[wbOffset++] = x % 10 + '0';
		x /= 10;
	}
	for (int l = st, r = wbOffset - 1; l < r; ++l, --r) {
		char t = writeBuffer[l];
		writeBuffer[l] = writeBuffer[r];
		writeBuffer[r] = t;
	}
}


IO& IO::operator <<(int x) {
	::printInt(x);
	return *this;
}


IO& IO::operator <<(ostream& (*fn)(ostream&)) {
	::newline();
	return *this;
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
	size = (size == -1 ? sz(edges) : min(size, sz(edges)));
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


void UndirectedGraph::addBidirectionalEdge(const int _from, const int _to) {
	addDirectedEdge(_from, _to);
	addDirectedEdge(_to, _from);
}

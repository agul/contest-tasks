#pragma comment(linker, "/STACK:66777216")
#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
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
#pragma hdrstop

using namespace std;

#ifdef _MSC_VER
#include <intrin.h>
#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#endif

#define sz(a) ((int)a.size())
#define X first
#define Y second
#define mp make_pair

#define ll long long
#define vi vector<int>
#define vvi vector<vi>

const ll LINF = 0x3f3f3f3f3f3f3f3fLL;


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
	inline void nextString(char * s);

	IO& operator >>(int& x);
	IO& operator >>(char * s);

	void newline();

	void printInt(int x);
	void printString(const char * s);

	IO& operator <<(int x);
	IO& operator <<(const char * s);
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


inline void nextString(char * s) {
	if (useFastIO) {
		io.nextString(s);
		return;
	}
	*pin >> s;
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


inline void printString(const char * s) {
	if (useFastIO) {
		io.printString(s);
		return;
	}
	*pout << s;
}


template<class T> inline T sqr(const T& x) {
	return x * x;
}


namespace Random {


}


class DoubleHasher_t {
public:
	static const int MA = 1e9 + 7, MB = 1e9 + 9;

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

	bool operator == (const DoubleHasher_t &x) const {
		return a == x.a && b == x.b;
	}


};

template<class T> class Hasher {
public:

	T * deg, * hash;
	int P;
	const char * str;

	Hasher(const int n, const int P = max(rand(), 307)) : P(P) {
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

	void hashString(const char * s, int n = 0) {
		str = s;
		if (!n) {
			n = strlen(s);
		}
		hash[0] = 0;
		for (int i = 0; i < n; ++i) {
			hash[i + 1] = hash[i] * P + s[i];
		}
	}


	T getHash(const int l, const int r) const {
		return hash[r] - hash[l - 1] * deg[r - l + 1];
	}


private:


};


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

	bool isSparse() const {
		return !vertexCount || sqr(static_cast<ll>(vertexCount)) >= (edgesCount << 4);
	}

	void clear(int size = -1);
	void deepClear();

	int addDirectedEdge(const int _from, const int _to);
	int addDirectedWeightedEdge(const int _from, const int _to, const ll _weight);

	void dijkstra(int startVertex, ll dist[], int last[] = NULL) const;
	ll dijkstra(int startVertex, int finishVertex, int path[] = NULL) const;


private:

};


int __;
IO io;
const int MAXN = 333;
const int MAXL = 111111;

int n, k, len[MAXN], lcp[MAXN][MAXN], path[MAXN * MAXN];
char s[MAXL];
Hasher<DoubleHasher_t>* hashes[MAXN];
Graph graph(MAXN * MAXN, MAXN * MAXN, Graph::GT_WEIGHTED);

int calcLCP(int x, int y) {
	int L = 0, R = min(len[x], len[y]) + 1;
	while (R - L > 1) {
		int M = ((L + R) >> 1);
		if (hashes[x]->getHash(1, M) == hashes[y]->getHash(1, M)) {
			L = M;
		}
		else {
			R = M;
		}
	}
	return L;
}

void solve(istream& ins, ostream& out) {
	// io.assignFilesInputTxt();
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		cerr << _ << endl;
		io >> n >> k;
		for (int i = 1; i <= n; ++i) {
			delete hashes[i];
			io >> s;
			len[i] = strlen(s);
			hashes[i] = new Hasher<DoubleHasher_t>(len[i], 307);
			hashes[i]->hashString(s, len[i]);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				lcp[i][j] = lcp[j][i] = calcLCP(i, j);
			}
		}
		graph.clear();
		graph.initGraph(2 + n * k);
		for (int i = 1; i <= n; ++i) {
			graph.addDirectedWeightedEdge(0, i, len[i]);
		}
		for (int i = 0; i < k - 1; ++i) {
			for (int j = 1; j <= n; ++j) {
				for (int q = j + 1; q <= n; ++q) {
					if (j == q) {
						continue;
					}
					graph.addDirectedWeightedEdge(i * n + j, (i + 1) * n + q, len[j] + len[q] - (lcp[j][q] << 1));
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			graph.addDirectedWeightedEdge((k - 1) * n + i, n * k + 1, len[i]);
		}
		int ans = graph.dijkstra(0, n * k + 1, path);
		io << "Case #" << _ + 1 << ": " << ans + k << endl;
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


inline void IO::nextString(char * s) {
	if (!curChar) {
		rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
		if (rbCount <= 0) {
			eof = true;
			return;
		}
		rbOffset = 0;
		curChar = readBuffer[rbOffset++];
	}
	while (!eof && (curChar == ' ' || curChar == '\n')) {
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				return;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	int ind = 0;
	while (!eof && curChar != ' ' && curChar != '\n') {
		s[ind++] = curChar;
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				s[ind] = 0;
				return;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	s[ind] = 0;
}

/* inline void IO::nextLine(char * s) {
	if (!curChar) {
		rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
		if (rbCount <= 0) {
			eof = true;
			return;
		}
		rbOffset = 0;
		curChar = readBuffer[rbOffset++];
	}
	int ind = 0;
	while (!eof && curChar != '\n') {
		s[ind++] = curChar;
		// shiftChar begin
		if (rbOffset == rbCount) {
			rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
			if (rbCount <= 0) {
				eof = true;
				s[ind] = 0;
				return;
			}
			rbOffset = 0;
		}
		curChar = readBuffer[rbOffset++];
		// shiftChar end
	}
	s[ind] = 0;
	// shiftChar begin
	if (rbOffset == rbCount) {
		rbCount = fread(readBuffer, sizeof(readBuffer[0]), sizeof(readBuffer), stdin);
		if (rbCount <= 0) {
			eof = true;
			return;
		}
		rbOffset = 0;
	}
	curChar = readBuffer[rbOffset++];
	// shiftChar end
} */

IO& IO::operator >>(int& x) {
	x = ::nextInt();
	return *this;
}


IO& IO::operator >>(char * s) {
	::nextString(s);
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


void IO::printString(const char * s) {
	for (int i = 0; s[i]; ++i) {
		if (wbOffset == BUFFER_SIZE) {
			// flush begin
			fwrite(writeBuffer, sizeof(writeBuffer[0]), wbOffset, stdout);
			wbOffset = 0;
			// flush end
		}
		writeBuffer[wbOffset++] = s[i];
	}
}


IO& IO::operator <<(int x) {
	::printInt(x);
	return *this;
}


IO& IO::operator <<(const char * s) {
	::printString(s);
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

int Graph::addDirectedWeightedEdge(const int _from, const int _to, const ll _weight) {
	weight[edgesCount] = _weight;
	return addDirectedEdge(_from, _to);
}


void Graph::dijkstra(int startVertex, ll dist[], int last[]) const {
	fill_n(dist, vertexCount, LINF);
	dist[startVertex] = 0;
	if (last != NULL) {
		fill_n(last, vertexCount, -1);
	}
	if (isSparse()) {
		priority_queue<pair<ll, int>> q;
		q.push(mp(0, startVertex));
		while (!q.empty()) {
			auto it = q.top();
			q.pop();
			int curVertex = it.Y;
			ll curlen = -it.X;
			if (curlen > dist[curVertex]) {
				continue;
			}
			for (auto& it : edges[curVertex]) {
				ll newlen = curlen + weight[it];
				int toVertex = to[it];
				if (dist[toVertex] > newlen) {
					dist[toVertex] = newlen;
					q.push(mp(-newlen, toVertex));
					last[toVertex] = it;
				}
			}
		}
	} else {
		bool * used = new bool[vertexCount];
		fill_n(used, vertexCount, false);
		for (int i = 0; i < vertexCount; ++i) {
			int index = -1;
			ll curlen = LINF;
			for (int j = 0; j < vertexCount; ++j) {
				if (!used[j] && dist[j] < curlen) {
					curlen = dist[j];
					index = j;
				}
			}
			if (index == -1) {
				break;
			}
			used[index] = true;
			for (auto& it : edges[index]) {
				int toVertex = to[it];
				ll newlen = curlen + weight[it];
				if (!used[toVertex] && dist[toVertex] > newlen) {
					dist[toVertex] = newlen;
					last[toVertex] = it;
				}
			}
		}
		delete[] used;
	}
}

ll Graph::dijkstra(int startVertex, int finishVertex, int path[]) const {
	if (startVertex == finishVertex) {
		return 0;
	}
	ll * dist = new ll[vertexCount];
	int * last = NULL;
	if (path != NULL) {
		last = new int[vertexCount];
	}
	dijkstra(startVertex, dist, last);
	if (path != NULL) {
		fill_n(path, vertexCount, -1);
		int pathSize = 0, curVertex = finishVertex;
		while (curVertex != startVertex) {
			int curEdge = last[curVertex];
			path[pathSize++] = curEdge;
			curVertex = from[curEdge];
		}
		reverse(path, path + pathSize);
		delete[] last;
	}
	ll ans = dist[finishVertex];
	delete[] dist;
	return ans;
}

#include "Head.h"
#include "IO.h"
#include "Hasher.h"
#include "Graph.h"

int __;
IO io;
const int MOD = 1000000007;
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

#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

struct Node {
	int l, r;
	int v;

	Node() : Node(0, 0, 0) {}
	Node(int l, int r, int v) : l(l), r(r), v(v) {}

	bool operator < (const Node& rhs) const {
		return l < rhs.l || (l == rhs.l && r < rhs.r) || (l == rhs.l && r == rhs.r && v < rhs.v);
	}

};

void solve(istream& ins, ostream& out) {
	int n, root;
	io >> n >> root;
	set<Node> nodes;
	nodes.emplace(-INF, root, root);
	nodes.emplace(root, INF, root);
	for (int i = 1; i < n; ++i) {
		int x;
		io >> x;
		auto it = nodes.lower_bound({ x, x, x });
		--it;
		auto node = *it;
		nodes.erase(it);

		io << node.v << " ";
		nodes.emplace(node.l, x, x);
		nodes.emplace(x, node.r, x);

	}
}

#include "Head.h"
#include "IO/IO.h"
#include "Matrix.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

constexpr int factorial(int n) {
	return n > 0 ? n * factorial(n - 1) : 1;
}

constexpr int fact[10] = {
	factorial(0),
	factorial(1),
	factorial(2),
	factorial(3),
	factorial(4),
	factorial(5),
	factorial(6),
	factorial(7),
	factorial(8),
	factorial(9)
};

inline int encode(const Matrix<int>& a) {
	int ret = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			ret = ret * 10 + a[i][j];
		}
	}
	return ret;
}

inline void decode(int val, Matrix<int>& a) {
	for (int i = 2; i >= 0; --i) {
		for (int j = 2; j >= 0; --j) {
			a[i][j] = val % 10;
			val /= 10;
		}
	}
}

int h, t, q[fact[9]][5];
unordered_set<int> used, happy;

void add(int x, int len, char dir, int val, int prev) {
	if (used.count(x)) {
		return;
	}
	used.insert(x);
	q[t][0] = x;
	q[t][1] = len;
	q[t][2] = dir;
	q[t][3] = val;
	q[t][4] = prev;
	++t;
}

void rotate_row(Matrix<int>& a, int row) {
	int tmp = a[row][0];
	a[row][0] = a[row][1];
	a[row][1] = a[row][2];
	a[row][2] = tmp;
}

void rotate_col(Matrix<int>& a, int col) {
	int tmp = a[0][col];
	a[0][col] = a[1][col];
	a[1][col] = a[2][col];
	a[2][col] = tmp;
}

void get_ans(int pos) {
	vector<string> ans;
	while (pos > 0) {
		string t = "";
		t += q[pos][2];
		t += to_string(q[pos][3]);
		ans.emplace_back(t);
		pos = q[pos][4];
	}
	reverse(all(ans));
	io << ans.size() << endl;
	for (const auto& it : ans) {
		io << it << endl;
	}
}

void solve(istream& ins, ostream& out) {
	Matrix<int> a(3, 3);
	happy = { 816357492, 618753294, 438951276, 276951438, 834159672, 492357816, 294753618, 672159834 };
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			io >> a[i][j];
		}
	}
	h = t = 0;
	used.clear();
	add(encode(a), 0, 0, 0, 0);
	while (h < t) {
		int cur_val = q[h][0];
		decode(cur_val, a);
		int cur_len = q[h][1];
		if (happy.count(cur_val)) {
			get_ans(h);
			return;
		}
		for (int i = 0; i < 3; ++i) {
			rotate_row(a, i);
			add(encode(a), cur_len + 1, 'L', i + 1, h);
			rotate_row(a, i);
			add(encode(a), cur_len + 1, 'R', i + 1, h);
			rotate_row(a, i);
			rotate_col(a, i);
			add(encode(a), cur_len + 1, 'U', i + 1, h);
			rotate_col(a, i);
			add(encode(a), cur_len + 1, 'D', i + 1, h);
			rotate_col(a, i);
		}
		++h;
	}
}

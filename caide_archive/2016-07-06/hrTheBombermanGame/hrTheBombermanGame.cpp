#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void output(const vector<string>& a, ostream& out) {
	for (const auto& it : a) {
		out << it << endl;
	}
}

std::vector<std::string> process(const vector<string>& a) {
	int n = a.size();
	int m = a.front().size();
	vector<string> b = a;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] != 'O') {
				continue;
			}
			b[i][j] = 'O';
			for (int dir = 0; dir < 4; ++dir) {
				int nx = i + DX[dir];
				int ny = j + DY[dir];
				if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
					continue;
				}
				b[nx][ny] = 'O';
			}
		}
	}
	auto xored = a;
	bool any = false;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			xored[i][j] = (b[i][j] == 'O' ? '.' : 'O');
		}
	}
	return xored;
}

void solve(std::istream& in, std::ostream& out) {
	int n, m, steps;
	in >> n >> m >> steps;
	vector<string> a(n);
	in >> a;
	--steps;
	auto xored = process(a);
	if (steps == 0) {
		output(a, out);
		return;
	}
	if (steps % 4 == 0) {
		output(process(xored), out);
		return;
	}
	if (steps % 4 == 1 || steps % 4 == 3) {
		for (auto& row : a) {
			for (auto& cell : row) {
				cell = 'O';
			}
		}
		output(a, out);
		return;
	}
	output(xored, out);
}

#include "base/header.hpp"
#include "string_utils.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	auto keys = make_vector<int>(4, 3, 0);
	int cnt = 1;
	for (auto& row : keys) {
		for (auto& cell : row) {
			cell = cnt++;
		}
	}
	keys[3][1] = 0;
	std::vector<pii> but(10);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			const int cell = keys[i][j]; 
			if (cell > 9) {
				continue;
			}
			but[cell] = { i, j };
		}
	}
	std::string s;
	int n;
	in >> n >> s;
	std::vector<pii> pos;
	for (const auto& ch : s) {
		const int x = dig(ch);
		pos.emplace_back(but[x]);
	}
	for (int dir = 0; dir < 4; ++dir) {
		bool ok = true;
		for (const auto& it : pos) {
			int nx = it.first + DX[dir];
			int ny = it.second + DY[dir];
			if (nx < 0 || ny < 0 || nx >= 4 || ny >= 3 || keys[nx][ny] > 9) {
				ok = false;
				break;
			}
		}
		if (ok) {
			out << "NO" << endl;
			return;
		}
	}
	out << "YES" << endl;
}

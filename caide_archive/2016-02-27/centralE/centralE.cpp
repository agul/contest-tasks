#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

char s[32][32];

void solve(istream& ins, ostream& out) {
	vector<pii> points;
	for (int i = 0; i < 16; ++i) {
		io >> s[i];
		for (int j = 0; j < 16; ++j) {
			if (s[i][j] == '#') {
				points.emplace_back(i, j);
			}
		}
	}
	vector<pii> best = points;
	int ax = 0, ay = 0;
	for (int dx = 0; dx < 16; ++dx) {
		for (int dy = -15; dy < 16; ++dy) {
			vector<pii> obj;
			set<pii> used;
			bool ok = true;
			for (const auto& p : points) {
				if (used.count({ p.X, p.Y })) {
					continue;
				}
				int x = p.X + dx;
				int y = p.Y + dy;
				if (x >= 0 && y >= 0 && x < 16 && y < 16 && s[x][y] == '#') {
					obj.push_back(p);
					used.insert(p);
					used.insert({ x, y });
				} else {
					x = p.X - dx;
					y = p.Y - dy;
					if (x >= 0 && y >= 0 && x < 16 && y < 16 && s[x][y] == '#') {
						obj.emplace_back(x, y);
						used.insert(p);
						used.insert({ x, y });
					}
					else {
						ok = false;
					}
				}
			}
			if (ok && obj.size() < best.size()) {
				ax = dx, ay = dy;
				best.swap(obj);
			}
		}
	}
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 16; ++j) {
			s[i][j] = '.';
		}
	}
	for (const auto& p : best) {
		s[p.X][p.Y] = '#';
	}
	io << ay << " " << ax << endl;
	for (int i = 0; i < 16; ++i) {
		io << s[i] << endl;
	}
	return;
}

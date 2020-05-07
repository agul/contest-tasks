#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

struct Event {
	int type;
	int index;
	int color;
	int time;

	Event() {}
	Event(int type, int index, int color, int time) : type(type), index(index), color(color), time(time) {}

	bool operator < (const Event& rhs) const {
		return time < rhs.time;
	}

};

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m >> __;
	vector<pii> rows(n, { -1, 0 });
	vector<pii> cols(m, { -1, 0 });
	vector<vector<int>> ans(n, vector<int>(m, 0));
	for (int _ = 0; _ < __; ++_) {
		int x, y, z;
		io >> x >> y >> z;
		--y;
		(x == 1 ? rows : cols)[y] = { _, z };
	}
	vector<Event> events;
	for (int i = 0; i < n; ++i) {
		events.emplace_back(0, i, rows[i].Y, rows[i].X);
	}
	for (int i = 0; i < m; ++i) {
		events.emplace_back(1, i, cols[i].Y, cols[i].X);
	}
	sort(all(events));
	for (const auto& ev : events) {
		if (ev.type) {
			for (int i = 0; i < n; ++i) {
				ans[i][ev.index] = ev.color;
			}
		}
		else {
			for (int i = 0; i < m; ++i) {
				ans[ev.index][i] = ev.color;
			}
		}
	}
	for (const auto& row : ans) {
		for (const auto& col : row) {
			io << col << ' ';
		}
		io << endl;
	}
}

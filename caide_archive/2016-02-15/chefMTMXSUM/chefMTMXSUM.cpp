#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

struct Event {

	enum Type {
		GROW,
		DIE
	};

	int start_time;
	int end_time;
	Type type;
	int index;

	Event() : Event(0, 0, GROW, 0) {}

	Event(int start_time, int end_time, Type type, int index) : start_time(start_time), end_time(end_time), type(type), index(index) {}

	bool operator < (const Event& rhs) const {
		return	start_time < rhs.start_time ||
			(start_time == rhs.start_time && end_time < rhs.end_time) ||
			(start_time == rhs.start_time && end_time == rhs.end_time && type < rhs.type) ||
			(start_time == rhs.start_time && end_time == rhs.end_time && type == rhs.type && index < rhs.index);
	}

};

int left_max[MAXN * 4], right_max[MAXN * 4];

void push(int tree[], int v) {
	if (tree[v] != -1) {
		tree[v << 1] = tree[(v << 1) ^ 1] = tree[v];
		tree[v] = -1;
	}
}

void update(int tree[], int v, int tl, int tr, int l, int r, int color) {
	if (l > r) {
		return;
	}
	if (l == tl && tr == r) {
		tree[v] = color;
		return;
	}
	push(tree, v);
	int tm = (tl + tr) / 2;
	update(tree, v << 1, tl, tm, l, min(r, tm), color);
	update(tree, (v << 1) ^ 1, tm + 1, tr, max(l, tm + 1), r, color);
}

int get(int tree[], int v, int tl, int tr, int pos) {
	if (tl == tr) {
		return tree[v];
	}
	push(tree, v);
	int tm = (tl + tr) / 2;
	if (pos <= tm) {
		return get(tree, v << 1, tl, tm, pos);
	}
	return get(tree, (v << 1) ^ 1, tm + 1, tr, pos);
}

void generate_events(const std::vector<ll>& vec, std::vector<ll>& sums) {
	int n = vec.size();
	vector<pii> a;
	for (int i = 0; i < n; ++i) {
		a.emplace_back(static_cast<int>(vec[i]), i + 1);
	}
	sort(all(a), greater<pii>());
	fill_n(left_max, n * 4, -1);
	fill_n(right_max, n * 4, -1);
	update(left_max, 1, 1, n, 1, n, 0);
	update(right_max, 1, 1, n, 1, n, n + 1);
	for (const auto& pair : a) {
		int index = pair.Y;
		int cur_left = get(left_max, 1, 1, n, index);
		int cur_right = get(right_max, 1, 1, n, index);
		if (cur_left >= 1 && vec[cur_left - 1] == pair.X) {
			--cur_left;
		}
		update(right_max, 1, 1, n, cur_left + 1, index - 1, index);
		update(left_max, 1, 1, n, index + 1, cur_right - 1, index);
	}
	set<Event> events;
	for (int i = 1; i <= n; ++i) {
		int cur_left = get(left_max, 1, 1, n, i);
		int diff_left = i - cur_left - 1;
		int cur_right = get(right_max, 1, 1, n, i);
		int diff_right = cur_right - i - 1;
		int grow = min(diff_left, diff_right);
		int die = max(diff_left, diff_right);
		events.emplace(1, grow + 1, Event::GROW, i - 1);
		events.emplace(die + 2, die + 2 + grow, Event::DIE, i - 1);
	}
	ll sum = 0;
	sums.clear();
	Event max_event = Event(INF, INF, Event::GROW, INF);
	for (int timer = 1; timer <= n; ++timer) {
		Event next;
		for (;;) {
			auto it = events.lower_bound(next);
			if (it == events.end() || it->start_time > timer) {
				break;
			}
			if (it->type == Event::GROW) {
				add_mod(sum, vec[it->index] % MOD);
			}
			else {
				sub_mod(sum, vec[it->index] % MOD);
			}
			auto jt = it;
			++jt;
			if (jt == events.end()) {
				next = max_event;
			}
			else {
				next = *jt;
			}
			if (it->end_time == timer) {
				events.erase(it);
			}
		}
		sums.emplace_back(sum);
	}
}

void solve(istream& ins, ostream& out) {
	int n;
	ins >> n;
	vector<ll> a(n);
	vector<ll> b(n);
	for (int i = 0; i < n; ++i) {
		ins >> a[i];
		a[i] += i + 1;
	}
	for (int i = 0; i < n; ++i) {
		ins >> b[i];
		b[i] += i + 1;
	}
	vector<ll> sum_a;
	generate_events(a, sum_a);
	vector<ll> sum_b;
	generate_events(b, sum_b);
	for (int i = 0; i < n; ++i) {
		mul_mod(sum_a[i], sum_b[i]);
		out << sum_a[i] << ' ';
	}
	out << endl;
}

#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

struct item {
	int key, prior, cnt;
	item * l, *r;
	item() : cnt(0) { }
	item(int key, int prior, int cnt) : key(key), prior(prior), cnt(cnt), l(NULL), r(NULL) { }
};
typedef item * pitem;

int cnt(const pitem& t) {
	return t ? t->cnt : 0;
}

void upd_cnt(pitem& t) {
	if (t)
		t->cnt = 1 + cnt(t->l) + cnt(t->r);
}

void split(pitem& t, int key, pitem & l, pitem & r) {
	if (!t)
		l = r = NULL;
	else if (key < t->key)
		split(t->l, key, l, t->l), r = t;
	else
		split(t->r, key, t->r, r), l = t;
	upd_cnt(t);
}

void insert(pitem & t, pitem it) {
	if (!t)
		t = it;
	else if (it->prior > t->prior)
		split(t, it->key, it->l, it->r), t = it;
	else
		insert(it->key < t->key ? t->l : t->r, it);
	upd_cnt(t);
}

using Container = unordered_map<int, pitem>;
Container adding, deleting;

pitem& get_root(Container& map, int value) {
	return map[value];
}

void add_element(int value, int time) {
	auto& root = get_root(adding, value);
	auto node = new item(time, rand(), 0);
	insert(root, node);
}

void remove_element(int value, int time) {
	auto& root = get_root(deleting, value);
	auto node = new item(time, rand(), 0);
	insert(root, node);
}

int search_cnt(const pitem& root, int key, int ans) {
	if (root == NULL) {
		return 0;
	}
	if (root->key > key) {
		if (root->l == NULL) {
			return ans;
		}
		return search_cnt(root->l, key, ans);
	}
	if (root->key == key || root->r == NULL) {
		return ans + 1 + cnt(root->l);
	}
	return search_cnt(root->r, key, ans + 1 + cnt(root->l));
}

int get_count(Container& map, int value, int time) {
	auto& root = get_root(map, value);
	return search_cnt(root, time, 0);
}

int get_ans(int value, int time) {
	return get_count(adding, value, time) - get_count(deleting, value, time);
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	adding.clear();
	deleting.clear();
	for (int i = 0; i < n; ++i) {
		int type, time, value;
		io >> type >> time >> value;
		if (type == 1) {
			add_element(value, time);
		} else
		if (type == 2) {
			remove_element(value, time);
		}
		else {
			int ans = get_ans(value, time);
			io << ans << endl;
		}
	}
}

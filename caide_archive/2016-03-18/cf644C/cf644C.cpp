#include "Head.h"
#include "IO/IO.h"
#include "Hasher.h"
#include "HashMap.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void parse_url(const string& url, string& host, string& path) {
	host = "";
	path = "";
	int slash_cnt = 0;
	for (const auto& ch : url) {
		if (ch == '/') {
			++slash_cnt;
		}
		if (slash_cnt < 3) {
			host += ch;
		}
		else {
			path += ch;
		}
	}
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<string> a(n);
	for (auto& it : a) {
		ins >> it;
	}
	sort(all(a));
	a.resize(unique(all(a)) - a.begin());
	n = a.size();
	vector<string> host;
	vector<ll> path;
	host.reserve(n);
	path.reserve(n);
	Hasher<DoubleHasher_t> hasher(32);
	for (const auto& it : a) {
		string cur_host, cur_path;
		parse_url(it, cur_host, cur_path);
		host.emplace_back(cur_host);
		hasher.hashString(cur_path);
		path.emplace_back(static_cast<ll>(hasher.getHash(1, cur_path.length())));
	}
	Hasher<DoubleHasher_t> hasher_vec(MAXN);
	int cur_ind = 0;
	unordered_map<ll, vector<string>> urls;
	while (cur_ind < n) {
		int y = cur_ind;
		vector<ll> paths;
		while (y < n && host[cur_ind] == host[y]) {
			paths.emplace_back(path[y]);
			++y;
		}
		hasher_vec.hash_vector(paths);
		urls[static_cast<ll>(hasher_vec.getHash(1, paths.size()))].emplace_back(host[cur_ind]);
		cur_ind = y;
	}
	int ans = 0;
	for (const auto& it : urls) {
		if (it.second.size() > 1) {
			++ans;
		}
	}
	io << ans << endl;
	for (const auto& vec : urls) {
		if (vec.second.size() == 1) {
			continue;
		}
		for (const auto& it : vec.second) {
			io << it << ' ';
		}
		io << endl;
	}
}

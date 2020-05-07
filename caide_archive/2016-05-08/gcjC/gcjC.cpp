#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

struct Outfit {
	int jacket, pants, shirt;

	Outfit() : Outfit(0, 0, 0) {}
	Outfit(int j, int p, int s) : jacket(j), pants(p), shirt(s) {}

	bool operator < (const Outfit& rhs) const {
		return	jacket < rhs.jacket
			|| (jacket == rhs.jacket && pants < rhs.pants)
			|| (jacket == rhs.jacket && pants == rhs.pants && shirt < rhs.shirt);
	}

};

bool not_full(std::map<Outfit, int>& cnt, const int j, const int p, const int s, const int K) {
	int& x = cnt[{j, p, 0}];
	int& y = cnt[{j, 0, s}];
	int& z = cnt[{0, p, s}];
	if (x >= K || y >= K || z >= K) {
		return false;
	}
	++x;
	++y;
	++z;
	return true;
}

void gen_stupid(std::vector<Outfit>& a, const int J, const int P, const int S, const int K) {
	map<Outfit, int> cnt;
	for (int j = 1; j <= J; ++j) {
		for (int p = 1; p <= P; ++p) {
			for (int s = 1; s <= S; ++s) {
				if (j == p && j == s) {
					continue;
				}
				if (not_full(cnt, j, p, s, K)) {
					a.emplace_back(j, p, s);
				}
			}
		}
	}
	for (int i = 1; i <= J; ++i) {
		if (not_full(cnt, i, i, i, K)) {
			a.emplace_back(i, i, i);
		}
	}
}

void gen_all(std::vector<Outfit>& a, int J, int P, int S) {
	for (int i = 1; i <= J; ++i) {
		for (int j = 1; j <= P; ++j) {
			for (int k = 1; k <= S; ++k) {
				a.emplace_back(i, j, k);
			}
		}
	}
}

void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	io >> __;
	for (int _ = 1; _ <= __; ++_) {
		cerr << _ << endl;
		io << "Case #" << _ << ": ";
		int j, p, s, k;
		io >> j >> p >> s >> k;
		vector<Outfit> a;
		gen_stupid(a, j, p, s, k);
		io << a.size() << endl;
		for (const auto& it : a) {
			//io << it.jacket << " " << it.pants << " " << it.shirt << endl;
		}
		continue;
		gen_all(a, j, p, s);
		if (j == 3) {
			io << 0 << endl;
			continue;
		}
		size_t ans = 0;
		size_t best_mask = 0;
		for (size_t mask = 0; mask < (1 << a.size()); ++mask) {
			map<Outfit, int> cnt;
			for (size_t i = 0; i < a.size(); ++i) {
				if (mask & (1 << i)) {
					const auto& cur = a[i];
					cnt[{cur.jacket, cur.pants, 0}] += 1;
					cnt[{cur.jacket, 0, cur.shirt}] += 1;
					cnt[{0, cur.pants, cur.shirt}] += 1;
				}
			}
			bool ok = true;
			for (const auto& it : cnt) {
				ok &= it.second <= k;
			}
			if (ok && umax(ans, popcount(mask))) {
				best_mask = mask;
			}
		}
		io << ans << endl;
		for (size_t i = 0; i < a.size(); ++i) {
			if (best_mask & (1 << i)) {
				const auto& cur = a[i];
				// io << cur.jacket << " " << cur.pants << " " << cur.shirt << endl;
			}
		}
	}
}

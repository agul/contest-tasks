#include "Head.h"

const int MOD = 1000000007;
const int MAXN = 111111;

using namespace std;

class LCMGCD {
public:
    /// caide keep
    string isPossible(vector<int> x, int t) {
		
		vector<pii> a;
		for (const auto& it : x) {
			a.emplace_back(convert(it));
		}

		pii need = convert(t);

		std::vector<pii> l_g;
		std::vector<pii> g_l;

		std::vector<pii> l_l;
		std::vector<pii> g_g;
		std::vector<pii> e_e;
		std::vector<pii> e_g;
		std::vector<pii> e_l;
		std::vector<pii> g_e;
		std::vector<pii> l_e;

		for (const auto& it : a) {
			if (it.first < need.first && it.second < need.second) {
				l_l.emplace_back(it);
			} else
			if (it.first < need.first && it.second == need.second) {
				l_e.emplace_back(it);
			}
			else
			if (it.first > need.first && it.second == need.second) {
				g_e.emplace_back(it);
			}
			else
			if (it.first > need.first && it.second > need.second) {
				g_g.emplace_back(it);
			}
			else
			if (it == need) {
				e_e.emplace_back(it);
			} else
			if (it.first == need.first && it.second < need.second) {
				e_l.emplace_back(it);
			}
			else
			if (it.first == need.first && it.second > need.second) {
				e_g.emplace_back(it);
			}
			else 
			if (it.first > need.first && it.second < need.second) {
				g_l.emplace_back(it);
			} else
			if (it.first < need.first && it.second > need.second) {
				l_g.emplace_back(it);
			}
		}


		auto process = [](std::vector<pii>& a, std::vector<pii>& bad, const std::function<pii(const pii&, const pii&)>& op) {
			if (a.empty()) {
				return;
			}
			auto& cur = a.front();
			for (const auto& it : bad) {
				cur = op(cur, it);
			}
			bad.clear();
		};


		if (!l_g.empty()) {

			process(l_e, l_g, gcd);
			process(l_l, l_g, gcd);

			if (!g_e.empty() && !l_g.empty()) {
				auto cur = g_e.back();
				g_e.pop_back();
				for (const auto& it : l_g) {
					cur = gcd(cur, it);
				}
				l_e.emplace_back(cur);
				l_g.clear();
			}

			if (!l_g.empty()) {
				return ans(false);
			}
		}

		if (!g_l.empty()) {

			process(g_e, g_l, lcm);
			process(g_g, g_l, lcm);

			if (!g_l.empty()) {
				return ans(false);
			}
		}



		return ans(!e_e.empty());
    }

private:

	pii gcd(const pii& lhs, const pii& rhs) const {
		return{ min(lhs.first, rhs.first), min(lhs.second, rhs.second) };
	}

	pii lcm(const pii& lhs, const pii& rhs) const {
		return{ max(lhs.first, rhs.first), max(lhs.second, rhs.second) };
	}

	std::string ans(const bool f) const {
		return (f ? "" : "im") + std::string("possible");
	}

	bool easy(const std::vector<pii>& a, const pii& need) const {
		int x = 0;
		int y = 0;
		for (const auto& it : a) {
			umax(x, it.first);
			umax(y, it.second);
		}
		return pii(x, y) == need;
	}

	pii convert(int x) const {
		int a = 0;
		int b = 0;

		while (x % 2 == 0) {
			++a;
			x /= 2;
		}

		while (x % 3 == 0) {
			++b;
			x /= 3;
		}

		return{ a, b };
	}

};


string solve(vector<int> x, int t, int) {
    LCMGCD sol;
    return sol.isPossible(x, t);
}

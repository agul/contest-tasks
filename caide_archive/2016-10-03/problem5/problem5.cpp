#include "base/header.hpp"
#include "string_utils.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111;
const int MAXL = 2222;

std::bitset<MAXL> b[MAXN], cur_bit;

void to_bitset(const std::string& s, std::bitset<MAXL>& bit) {
	bit.reset();
	for (int i : range(s.length())) {
		if (isUpperCase(s[i])) {
			bit.set(i);
		}
	}
}

void solve(std::istream& in, std::ostream& out) {
	int k, n, m;
	in >> k >> n;
	vector<string> a(n);
	in >> a;

	std::unordered_map<std::string, std::vector<int>> str;
	int index = 0;
	for (const auto& it : a) {
		const string t = lowerCase(it);
		str[t].emplace_back(index);
		to_bitset(it, b[index]);
		++index;
	}

	in >> m;
	for (int i : range(m)) {
		string s;
		in >> s;
		int ans = 0;

		const string t = lowerCase(s);
		auto iter = str.find(t);
		if (iter == str.cend()) {
			out << 0 << endl;
			continue;
		}

		to_bitset(s, cur_bit);

		for (const auto j : iter->second) {
			if ((cur_bit ^ b[j]).count() <= k) {
				++ans;
			}
		}

		out << ans << endl;
	}
}

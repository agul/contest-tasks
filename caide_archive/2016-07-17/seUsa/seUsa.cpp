#include "base/header.hpp"
#include "string_utils.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 555;
const int MAXM = 256;

inline bool is_pow(const int n) {
	return (n & (n - 1)) == 0;
}

inline int get_value(const char ch) {
	return ch == '?' ? 10 : ch - '0';
}

void solve(std::istream& in, std::ostream& out) {
	ll n;
	std::array<bool, 11> vals;
	while (in >> n) {
		if (n == 0) {
			break;
		}
		string s;
		in >> s;
		if (!is_pow(s.length() + 1)) {
			out << -1 << endl;
			continue;
		} 
		if (s.length() == 1) {
			if (s == "?") {
				if (n >= 10) {
					out << -1 << endl;
				}
				else {
					out << n << endl;
				}
			}
			else {
				if (n != 1 || s == "0") {
					out << -1 << endl;
				}
				else {
					out << s << endl;
				}
			}
			continue;
		}
		--n;
		int max_pow = 0;
		while ((1 << max_pow) < s.length()) {
			++max_pow;
		}
		bool ok = true;
		std::vector<std::set<int>> available(max_pow);
		for (int i = 0; i < max_pow && ok; ++i) {
			const int start_pos = (1 << i) - 1;
			const int delta = (1 << (i + 1));
			int used = 10;
			for (auto& it : vals) {
				it = false;
			}
			for (int pos = start_pos; pos < s.length(); pos += delta) {
				if (pos > 0) {
					vals[get_value(s[pos - 1])] = true;
				}
				if (pos < s.length() - 1) {
					vals[get_value(s[pos + 1])] = true;
				}
				if (s[pos] == '?') {
					continue;
				}
				const int cur = get_value(s[pos]);
				if (used != 10 && used != cur) {
					ok = false;
					break;
				}
				used = cur;
			}
			if (used != 10) {
				if (!vals[used]) {
					available[i].insert(used);
				}
				continue;
			}
			for (int d : range(10)) {
				if (!vals[d]) {
					available[i].insert(d);
				}
			}
		}
		auto& first_vec = available.front();
		first_vec.erase(0);
		for (const auto& it : available) {
			ok &= !it.empty();
		}
		if (!ok) {
			out << -1 << endl;
			continue;
		}
		int fixed_first = -1;
		for (const auto& digit : first_vec) {
			ll total = 1;
			for (int i : range(1, max_pow)) {
				const ll cur = available[i].size() - available[i].count(digit);
				total *= cur;
			}
			if (n < total) {
				fixed_first = digit;
				break;
			}
			n -= total;
		}
		if (fixed_first == -1) {
			out << -1 << endl;
			continue;
		}
		for (int i : range(1, max_pow)) {
			available[i].erase(fixed_first);
		}
		vector<ll> suf(max_pow + 1);
		suf.back() = 1;
		for (int i : downrange(max_pow, 1)) {
			suf[i] = suf[i + 1] * available[i].size();
		}
		std::vector<int> digits{ fixed_first };
		for (int i : range(1, max_pow)) {
			int fixed_digit = -1;
			for (const auto& it : available[i]) {
				if (n < suf[i + 1]) {
					fixed_digit = it;
					break;
				}
				n -= suf[i + 1];
			}
			if (fixed_digit == -1) {
				ok = false;
				break;
			}
			digits.emplace_back(fixed_digit);
		}
		if (!ok) {
			out << -1 << endl;
			continue;
		}
		std::string ans(s.length(), '0');
		for (int i : range(max_pow)) {
			const int delta = (1 << (i + 1));
			for (int pos = (1 << i) - 1; pos < ans.length(); pos += delta) {
				ans[pos] = digits[i] + '0';
			}
		}
		out << ans << endl;
	}
}

#include "base/header.hpp"
#include "hash/hasher.hpp"
#include "hash/double_hasher.hpp"
#include "string/utils.hpp"

class BPetr {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        std::string s, a, b;
        in >> s >> a >> b;

        const int n = s.length();
        const int x = a.length();
        const int y = b.length();
        const int min_len = std::max(x, y);
        if (min_len > n) {
            out << 0 << std::endl;
            return;
        }

        Hasher<DoubleHasher<ll>> hash(s);
        const auto ha = Hasher<DoubleHasher<ll>>(a).get_hash(0, x - 1);
        const auto hb = Hasher<DoubleHasher<ll>>(b).get_hash(0, y - 1);
        int ans = 0;
        for (int len : inclusiveRange(min_len, n)) {
            std::set<DoubleHasher<ll>> used;
            for (int i : range(n)) {
                const int last_index = i + len - 1;
                if (last_index >= n) {
                    continue;
                }
                const int suffix_start = last_index + 1 - y;
                if (hash.get_hash(i, i + x - 1) == ha && hash.get_hash(suffix_start, last_index) == hb) {
                    debug(i, len);
                    used.emplace(hash.get_hash(i, last_index));
                }
            }
            ans += used.size();
        }
        out << ans << std::endl;
	}


	BPetr() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    std::string s, a, b;
	    in >> s >> a >> b;
        const int n = s.length();
        const int x = a.length();
        const int y = b.length();

        std::unordered_set<std::string> used;
        for (int i : range(n - std::max(x, y) + 1)) {
            std::string tmp = s.substr(i, x);
            if (tmp != a) {
                continue;
            }
            if (ends_with(tmp, b)) {
                used.emplace(tmp);
            }
            for (int j : range(i + x, n)) {
                tmp += s[j];
                if (ends_with(tmp, b)) {
                    used.emplace(tmp);
                }
            }
        }
        const int jans = used.size();

	    int pans;
	    out >> pans;

	    if (pans != jans) {
	        debug("WA", jans, pans);
	        return false;
	    }
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kAlphabetSize = 4;
	    const int kMaxn = 20;
	    const int kMaxm = 4;

	    const int n = Random::get(1, kMaxn);
	    std::string s(n, '$');
	    for (int i : range(n)) {
	        s[i] = Random::get(0, kAlphabetSize - 1) + 'a';
	    }

	    const int alen = Random::get(1, std::min(kMaxm, n));
	    const int apos = Random::get(0, n - alen);

	    const int blen = Random::get(1, std::min(kMaxm, n));
	    const int bpos = Random::get(0, n - blen);

	    test << s << std::endl;
	    test << s.substr(apos, alen) << std::endl;
	    test << s.substr(bpos, blen) << std::endl;
	}

};

#include "base/header.hpp"
#include "collections/bitset.hpp"
#include "collections/value_compressor.hpp"
#include "graph/dsu.hpp"

class BMnozhestva {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	static constexpr int kMaxn = 200;
	using bitset = Bitset<kMaxn>;

	void solve_slow(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        const int intersections = n * (n - 1) / 2;
        std::vector<bitset> cards;
        for (int i : range(intersections)) {
            bitset card;
            int k;
            in >> k;
            for (int j : range(k)) {
                int x;
                in >> x;
                card.set(x - 1);
            }
            cards.emplace_back(std::move(card));
        }

        std::vector<bitset> sets;
        for (int i : range(intersections)) {
            std::map<bitset, int> cnt;
            for (int j : range(i + 1, intersections)) {
                cnt[cards[i] & cards[j]]++;
            }
            for (const auto& it : cnt) {
                if (it.second == n - 2) {
                    sets.emplace_back(it.first);
                }
            }
        }

        for (const auto& set : sets) {
            out << set.count();
            for (int x : set.indices()) {
                out << " " << x + 1;
            }
            out << std::endl;
        }
	}

    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        const int intersections = n * (n - 1) / 2;
        std::unordered_set<int> used;
        std::vector<bitset> cards;
        for (int i : range(intersections)) {
            bitset card;
            int k;
            in >> k;
            for (int j : range(k)) {
                int x;
                in >> x;
                card.set(x - 1);
                used.emplace(x - 1);
            }
            cards.emplace_back(std::move(card));
        }

        DSU dsu(kMaxn);
        for (int x : range(kMaxn)) {
            if (!used.count(x)) {
                continue;
            }
            std::vector<int> count(kMaxn, 0);
            for (const auto& card : cards) {
                if (!card[x]) {
                    continue;
                }
                for (int y : range(x + 1, kMaxn)) {
                    if (card[y]) {
                        ++count[y];
                    }
                }
            }
            for (int y : range(x + 1, kMaxn)) {
                if (count[y] == n - 1) {
                    dsu.unite(x, y);
                }
            }
        }

        dsu.finalize();
        std::vector<std::vector<int>> ans(n);
        IntegralValueCompressor<int> compressor;
        for (int x : range(kMaxn)) {
            if (!used.count(x)) {
                continue;
            }
            const int compressed_index = compressor[dsu.find_set(x)];
            ans[compressed_index].emplace_back(x);
        }

        if (n == 2) {
            ans[1] = std::vector<int>{ans[0].back()};
            ans[0].pop_back();
        }

        for (const auto& set : ans) {
            out << set.size();
            for (const int x : set) {
                out << " " << x + 1;
            }
            out << std::endl;
        }
	}

	BMnozhestva() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

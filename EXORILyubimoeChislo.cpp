#include "base/header.hpp"

class EXORILyubimoeChislo {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	static const int kBlockSize = 333;

	struct Query {
		int left;
		int right;
		int id;

		Query() : Query(0, 0, 0) {}
		Query(int l, int r, int id) : left(l), right(r), id(id) {}
	};

	void solve(std::istream& in, std::ostream& out) {
		int n, m, k;
		in >> n >> m >> k;
		std::vector<int> a(n);
		in >> a;

		std::vector<Query> q;
		q.reserve(m);
		for (int i : range(m)) {
			int l, r;
			in >> l >> r;
			q.emplace_back(l, r, i);
		}
		sort(q, [](const Query& lhs, const Query& rhs) {
			const int left_id = (lhs.left - 1) / kBlockSize;
			const int right_id = (rhs.left - 1) / kBlockSize;
			return (left_id == right_id && lhs.right < rhs.right) || left_id < right_id;
		});

		std::vector<int> prefs = {0};
		prefs.reserve(n + 1);
		for (int x : a) {
			prefs.emplace_back(prefs.back() ^ x);
		}

		ll res = 0;
		std::vector<int> cnt(1 << 20, 0);

		auto add = [&res, &cnt, k, &prefs](const int index) {
			// debug("add", index);
			const int cur_value = prefs[index];
			res += cnt[cur_value ^ k];
			++cnt[cur_value];
		};

		auto del = [&res, &cnt, k, &prefs](const int index) {
			// debug("del", index);
			const int cur_value = prefs[index];
			--cnt[cur_value];
			res -= cnt[cur_value ^ k];
		};

		std::vector<ll> ans(m, -1);
		int cur_left = 1;
		int cur_right = 0;
		cnt[0] = 1;
		// debug(prefs);
		for (const auto& query : q) {
			// debug(query.id, cur_left, cur_right, query.left, query.right);
			while (cur_right > query.right) {
				del(cur_right);
				--cur_right;
			}
			while (cur_right < query.right) {
				++cur_right;
				add(cur_right);
			}
			// debug(cur_right, res);

			while (cur_left < query.left) {
				del(cur_left - 1);
				++cur_left;
			}
			while (cur_left > query.left) {
				--cur_left;
				add(cur_left - 1);
			}
			// debug(cur_left, res);

			ans[query.id] = res;
		}
		for (const auto& x : ans) {
			out << x << std::endl;
		}
	}


	EXORILyubimoeChislo() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n, m, k;
		in >> n >> m >> k;
		std::vector<int> a(n);
		in >> a;

		for (int test_id : range(1, m + 1)) {
			int x, y;
			in >> x >> y;
			--x;
			--y;

			int jans = 0;
			for (int i : inclusiveRange(x, y)) {
				int cur = 0;
				for (int j : inclusiveRange(i, y)) {
					cur ^= a[j];
					if (cur == k) {
						++jans;
					}
				}
			}

			int pans;
			out >> pans;

			if (jans != pans) {
				debug("FAIL", test_id, jans, pans);
				return false;
			}
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 100;
		const int kMaxm = 100;
		const int kMaxk = 100;

		const int n = Random::get(1, kMaxn);
		const int m = Random::get(1, kMaxm);
		const int k = Random::get(0, kMaxk);
		test << n << " " << m << " " << k << std::endl;
		for (int i : range(n)) {
			test << Random::get(0, kMaxk) << " ";
		}
		test << std::endl;
		for (int i : range(m)) {
			const int x = Random::get(1, n);
			const int y = Random::get(x, n);
			test << x << " " << y << std::endl;
		}
	}

};

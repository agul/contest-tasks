#include "base/header.hpp"
#include "collections/stack/stack.hpp"

class EAntonIIra {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		std::vector<int> p(n), s(n);
		in >> p >> s;

		for (auto& x : p) {
			--x;
		}

		std::vector<int> positions(n);
		for (int i : range(n)) {
			auto& x = s[i];
			--x;
			positions[x] = i;
		}

		auto go_left = [&positions, &p](const int index) {
			const int value = p[index];
			return positions[value] < index;
		};

		auto go_right = [&positions, &p](const int index) {
			const int value = p[index];
			return positions[value] > index;
		};

		std::vector<pii> ans;
		Stack<int> stack(n);

		auto process_swap = [&ans, &positions, &p, &stack](const int index) {
			const int value = p[index];
			const int to = stack.pop();
			ans.emplace_back(index, to);
			std::swap(p[index], p[to]);
			return to;
		};

		int index = n - 1;
		while (index >= 0) {
			if (go_right(index)) {
				index = process_swap(index);
			} else {
				if (go_left(index)) {
					stack.push(index);
				}
				--index;
			}
		}

		const ll total_sum = std::accumulate(all(ans), 0LL, [](const ll acc, const pii& rhs) {
			return acc + std::abs(rhs.X - rhs.Y);
		});
		printf("%lld\n%d\n", total_sum, ans.size());
		for (const auto& it : ans) {
			printf("%d %d\n", it.X + 1, it.Y + 1);
		}
//		out << total_sum << std::endl;
//		out << ans.size() << std::endl;
//		for (const auto& it : ans) {
//			out << it.X + 1 << " " << it.Y + 1 << std::endl;
//		}
	}


	EAntonIIra() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n;
		in >> n;

		std::vector<int> p(n), s(n);
		in >> p >> s;
		std::vector<int> positions(n + 1);
		for (int i : range(n)) {
			positions[s[i]] = i;
		}

		auto compare = [&p, &positions](const int index) {
			const int value = p[index];
			if (positions[value] < index) {
				return -1;
			}
			if (positions[value] > index) {
				return 1;
			}
			return 0;
		};

		ll pans;
		out >> pans;

		int k;
		out >> k;
		ll total = 0;
		for (int i : range(k)) {
			int x, y;
			out >> x >> y;

			const int a = compare(x - 1);
			const int b = compare(y - 1);

			std::swap(p[x - 1], p[y - 1]);

			if (std::abs(compare(x - 1) - b) > 1 || std::abs(compare(y - 1) - a) > 1) {
				debug("inefficient swap", x, y);
				return false;
			}

			total += std::abs(x - y);
		}

		if (total != pans) {
			debug(total, pans);
			return false;
		}

		if (p != s) {
			debug(p);
			debug(s);
			return false;
		}

//		ll jans;
//		jury >> jans;
//		if (jans != pans) {
//			debug(jans, pans);
//			return false;
//		}


		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 500;

		const int n = Random::get(1, kMaxn);
#ifdef USE_JNGEN
		jngen::setMod().add1();
		auto p = jngen::Array::id(n).shuffled();
		auto s = jngen::Array::id(n).shuffled();
		test << n << std::endl;
		test << p << std::endl;
		test << s << std::endl;
#endif
	}

};

#include "base/header.hpp"
#include "containers/stack/stack.hpp"
#include "data_structures/sparse_table.hpp"

class DDruzyaIPosledovatelnosti {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	template<typename Range>
	std::vector<int> find_next(const std::vector<int>& a, const Range& range, const std::function<bool(const int, const int)>& cmp, const int default_value) {
		const int n = a.size();
		std::vector<int> res(n, default_value);
		Stack<int> values(n);
		for (int i : range) {
			const int cur_value = a[i];
			while (!values.empty() && cmp(cur_value, a[values.top()])) {
				values.pop();
			}
			if (!values.empty()) {
				res[i] = values.top();
			}
			values.push(i);
		}
		return res;
	};

	struct SegmentSet {
		int l_from;
		int l_to;
		int r_from;
		int r_to;

		SegmentSet intersect(const SegmentSet& rhs) const {
			return {std::max(l_from, rhs.l_from), std::min(l_to, rhs.l_to), std::max(r_from, rhs.r_from), std::min(r_to, rhs.r_to)};
		}

		ll count() const {
			return std::max<ll>(0, l_to - l_from + 1) * std::max<ll>(0, r_to - r_from + 1);
		}

		bool inside_left(const int pos) const {
			return l_from <= pos && pos <= l_to;
		}

	};

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		auto a = make_vector<int>(n, 0);
		auto b = make_vector<int>(n, 0);
		in >> a >> b;

		const auto ge_left = find_next(a, range(n), std::greater<int>(), -1);
		const auto g_right = find_next(a, downrange(n), std::greater_equal<int>(), n);

		const auto le_left = find_next(b, range(n), std::less<int>(), -1);
		const auto l_right = find_next(b, downrange(n), std::less_equal<int>(), n);

		SafeUnorderedMap<int, std::vector<SegmentSet>> max_results;
		for (int i : range(n)) {
			max_results[a[i]].push_back({ge_left[i] + 1, i, i, g_right[i] - 1});
		}

		SafeUnorderedMap<int, size_t> max_pos;
		for (const auto& it : max_results) {
			max_pos[it.first] = 0;
		}

		ll ans = 0;
		for (int i : range(n)) {
			const int cur_value = b[i];
			const int pos = i;
			const SegmentSet cur_segment = {le_left[i] + 1, i, i, l_right[i] - 1};

			const auto it = max_results.find(cur_value);
			if (it == max_results.cend()) {
				continue;
			}

			auto& iter = max_pos[cur_value];
			const auto& vec = it->second;
			ans += vec[iter].intersect(cur_segment).count();
			if (i == 4 && false) {
				debug(a);
				debug(b);
				debug(ans, iter);
				debug(cur_segment.l_from, cur_segment.l_to, cur_segment.r_from, cur_segment.r_to);
				debug(vec[iter].l_from, vec[iter].l_to, vec[iter].r_from, vec[iter].r_to);
			}
			while (iter < vec.size() && vec[iter].l_from <= pos) {
				if (i == 4 && false) {
					debug('x');
					debug(ans, iter);
					debug(cur_segment.l_from, cur_segment.l_to, cur_segment.r_from, cur_segment.r_to);
					debug(vec[iter].l_from, vec[iter].l_to, vec[iter].r_from, vec[iter].r_to);
				}
				if (iter + 1 < vec.size() && vec[iter + 1].l_from <= pos) {
					++iter;
					ans += vec[iter].intersect(cur_segment).count();
				} else {
					break;
				}
			}
		}
		out << ans << std::endl;
	}


	DDruzyaIPosledovatelnosti() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n;
		in >> n;
		auto a = make_vector<int>(n, 0);
		auto b = make_vector<int>(n, 0);
		in >> a >> b;

		SparseTableCmp<int, std::greater<int>> max_table(a);
		SparseTableCmp<int> min_table(b);

		int jans = 0;
		for (int i : range(n)) {
			for (int j : range(i, n)) {
				const int x = max_table.query(i, j + 1);
				const int y = min_table.query(i, j + 1);
				if (a[x] == b[y]) {
					// debug(i, j);
					++jans;
				}
			}
		}

		ll pans;
		out >> pans;
		if (jans != pans) {
			debug(jans, pans);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static void generate_test(std::ostream& out) {
		const int kMaxn = 1000;
		const int kMaxValue = 5;
		const int kMinValue = 0;

		const int n = Random::get(1, kMaxn);
		out << n << std::endl;
		for (int i : range(n)) {
			const int value = Random::get(kMinValue, kMaxValue);
			out << value << " ";
		}
		out << std::endl;
		for (int i : range(n)) {
			const int value = Random::get(kMinValue, kMaxValue);
			out << value << " ";
		}
		out << std::endl;
	}

};

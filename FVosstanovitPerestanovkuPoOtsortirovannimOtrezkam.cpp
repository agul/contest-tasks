#include "base/header.hpp"

class FVosstanovitPerestanovkuPoOtsortirovannimOtrezkam {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n - 1, 0, 0);
			std::vector<SafeUnorderedSet<int>> sets;
			for (int i : range(n - 1)) {
				int m;
				in >> m;
				a[i] = make_vector<int>(m, 0);
				in >> a[i];
				for (int& x : a[i]) {
					--x;
				}
				sets.emplace_back(all(a[i]));
			}

			auto resolve = [&a, &sets, n, &out](const int x, const int y, const int start_pair_index) {
				std::vector<int> p(n, -1);
				p[0] = x;
				p[1] = y;
				SafeUnorderedSet<int> start_pair_set = sets[start_pair_index];

				std::vector<bool> used(n - 1, false);
				used[start_pair_index] = true;

				debug(x, y);
				for (int p_ind : range(2, n)) {
					std::vector<pii> candidates;
					for (int i : range(n - 1)) {
						if (used[i]) {
							continue;
						}
						auto cur_set = sets[i];
						for (int j : downrange(p_ind)) {
							auto it = cur_set.find(p[j]);
							if (it == cur_set.cend()) {
								break;
							} else {
								cur_set.erase(it);
							}
						}
						debug(i, cur_set);
						if (cur_set.size() != 1) {
							continue;
						}
						const int remaining_element = *cur_set.begin();
						if (start_pair_set.find(remaining_element) != start_pair_set.cend()) {
							continue;
						}
						candidates.emplace_back(i, remaining_element);
					}
					debug(candidates);
					if (candidates.size() != 1) {
						return false;
					}

					const int vec_ind = candidates.front().X;
					const int element = candidates.front().Y;
					used[vec_ind] = true;
					p[p_ind] = element;
				}
				for (int x : p) {
					out << x + 1 << " ";
				}
				out << std::endl;
				return true;
			};

			bool found = false;
			for (int start_pair_index : range(n)) {
				const auto& start_pair = a[start_pair_index];
				if (start_pair.size() > 2) {
					continue;
				}
				debug(start_pair_index);
				if (resolve(start_pair.front(), start_pair.back(), start_pair_index)
						|| resolve(start_pair.back(), start_pair.front(), start_pair_index)) {
					found = true;
					break;
				}
			}
			assert(found);
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};

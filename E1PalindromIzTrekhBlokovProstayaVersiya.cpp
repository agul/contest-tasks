#include "../algolib/cpplib/base/header.hpp"

const int kMaxN = 201;
int count[256];

class E1PalindromIzTrekhBlokovProstayaVersiya {
public:

	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;

			SafeUnorderedSet<int> diff_colors(all(a));

			std::vector<pii> b;
			b.emplace_back(a.front(), 0);
			for (int x : a) {
				if (x == b.back().first) {
					b.back().second += 1;
				} else {
					b.emplace_back(x, 1);
				}
			}

			int ans = 0;
			int round = 0;
			for (int color : range(kMaxN)) {
				// out << "NEW " << color << std::endl;
				fill(count, 0);
				int first = -1;
				int last = -1;
				for (int i : range(b.size())) {
					if (b[i].first == color) {
						if (first == -1) {
							first = i;
						}
						last = i;
					}
				}
				if (first == -1) {
					continue;
				}
				if (last == first) {
					umax(ans, b[first].second);
					continue;
				}
				for (int i : range(first + 1, last)) {
					if (b[i].first != color) {
						count[b[i].first] += b[i].second;
					}
				}
				int left = b[first].second;
				int right = b[last].second;
				while (first < last) {
					int max_color = 0;
					for (int k : range(kMaxN)) {
						umax(max_color, count[k]);
					}
					// out << color << " " << first << " " << left << " " << last << " " << right << " " << max_color << std::endl;

					if (max_color == 0) {
						break;
					}
					umax(ans, std::min(left, right) * 2 + max_color);
					if (left <= right) {
						++first;
						while (first < last && b[first].first != color) {
							count[b[first].first] -= b[first].second;
							++first;
						}
						if (first < last) {
							left += b[first].second;
						}
					} else {
						--last;
						while (first < last && b[last].first != color) {
							count[b[last].first] -= b[last].second;
							--last;
						}
						if (first < last) {
							right += b[last].second;
						}
					}
				}
				if (first == last) {
					umax(ans, left + right);
				}
			}
			out << ans << std::endl;
			// return;
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

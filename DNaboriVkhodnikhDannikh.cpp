#include "base/header.hpp"

class DNaboriVkhodnikhDannikh {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		auto a = make_vector<int>(n, 0);
		auto b = make_vector<int>(k, 0);
		in >> a >> b;

		b.insert(b.cbegin(), 0);
		sort(a);
		reverse(a);

		std::vector<std::vector<int>> ans;
		std::set<pii> arrays;

		for (int x : a) {
			const auto it = arrays.cbegin();
			int index = -1;
			if (it == arrays.cend() || it->first >= b[x]) {
				index = ans.size();
				ans.emplace_back(0);
			} else {
				index = it->second;
				arrays.erase(it);
			}
			ans[index].emplace_back(x);
			arrays.emplace(ans[index].size(), index);
		}



		out << ans.size() << std::endl;
		for (const auto& test : ans) {
			out << test.size();
			for (int x : test) {
				out << " " << x;
			}
			out << std::endl;
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

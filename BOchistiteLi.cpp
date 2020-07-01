#include "base/header.hpp"
#include "collections/stack/stack.hpp"

class BOchistiteLi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		std::string s;
		in >> n >> s;
		std::vector<std::pair<char, int>> a;
		for (char ch : s) {
			if (a.empty() || a.back().first != ch) {
				a.emplace_back(ch, 1);
			} else {
				a.back().second += 1;
			}
		}
		debug(a);


		Stack<std::pair<char, int>> stack(a.size());
		reverse(a);

		int index = 0;
		while (index < a.size()) {
			if (stack.empty()) {
				stack.push(a[index]);
				++index;
				continue;
			}

			auto& top = stack.top();
			if (a[index].first == '1' && top.first == '0') {
				top.second = 1;
				++index;
				continue;
			}

			if (stack.empty() || stack.top().first != a[index].first) {
				stack.push(a[index]);
				++index;
				continue;
			}

			if (stack.top().first == a[index].first) {
				stack.top().second += a[index].second;
				++index;
				continue;
			}
			assert(false);
		}

		std::string ans;
		const auto& vec = stack.data();
		for (const auto& it : reversed(vec)) {
			ans += std::string(it.second, it.first);
		}

		out << ans << std::endl;
	}


	BOchistiteLi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

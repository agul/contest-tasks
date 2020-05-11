#include "base/header.hpp"

class ARebus {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		std::getline(in, s);

		std::vector<std::string> tokens = {""};
		tokens.reserve(s.size());
		for (char ch : s) {
			if (isspace(ch)) {
				if (tokens.empty() || !tokens.back().empty()) {
					tokens.emplace_back("");
				}
			} else {
				tokens.back() += ch;
			}
		}
		while (!tokens.empty() && tokens.back().empty()) {
			tokens.pop_back();
		}

		debug(tokens);
		const int N = std::stoi(tokens.back());

		bool plus = true;
		std::vector<int> ans;
		ans.reserve(tokens.size() / 2);
		int sum = 0;
		for (const std::string& token : tokens) {
			if (token == "+") {
				plus = true;
			}
			else if (token == "-") {
				plus = false;
			}
			else if (token == "=") {
				break;
			}
			else if (token == "?") {
				ans.emplace_back(plus ? 1 : -1);
				sum += ans.back();
			}
			else {
				assert(false);
			}
		}

		for (int& x : ans) {
			if (sum < N) {
				if (x > 0) {
					sum -= x;
					x = std::min(N, N - sum);
					sum += x;
				}
			}
			if (sum > N) {
				if (x < 0) {
					sum -= x;
					x = -std::min(N, sum - N);
					sum += x;
				}
			}
		}

		if (sum != N) {
			out << "Impossible" << std::endl;
			return;
		}

		out << "Possible" << std::endl;
		size_t index = 0;
		for (const auto& token : tokens) {
			if (token == "?") {
				out << abs(ans[index++]) << " ";
			} else {
				out << token << " ";
			}
		}
		out << std::endl;

	}


	ARebus() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};

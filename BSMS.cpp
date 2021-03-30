#include "base/header.hpp"

class BSMS {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        std::string s;
        in >> n;
        std::getline(in, s);
        std::getline(in, s);

        std::vector<int> sentences = {0};
        bool sentence_started = false;
        for (const char ch : s) {
            if (sentence_started) {
                ++sentences.back();
            }
            if (ch == ' ') {
                continue;
            }
            sentence_started = true;
            if (ch == '.' || ch == '?' || ch == '!') {
                ++sentences.back();
                sentences.emplace_back(0);
                sentence_started = false;
            }
        }

        debug(sentences);

        if (std::any_of(all(sentences), [&n](const int sentence) {
            return sentence > n;
        })) {
            out << "Impossible" << std::endl;
            return;
        }

        int ans = 0;
        int cur_message = 0;
        for (int x : sentences) {
            if (cur_message > 0) {
                ++cur_message;
            }
            if (cur_message + x > n) {
                ++ans;
                cur_message = 0;
            }
            cur_message += x;
        }
        if (cur_message > 0) {
            ++ans;
        }
        out << ans << std::endl;
	}


	BSMS() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

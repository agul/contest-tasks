#include "base/header.hpp"
#include "string/utils.hpp"

class AUrokiGrammatiki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	enum class PartOfSpeech : uint8_t {
	    Adjective,
	    Noun,
	    Verb,
	    Unknown
	};

	enum class Gender : uint8_t {
	    Masculine,
	    Feminine,
	    Unknown
	};

	using ParsedWord = std::pair<PartOfSpeech, Gender>;
    std::unordered_map<std::string, ParsedWord> endings;

    ParsedWord parse(const std::string& token) {
        for (const auto& parsed_word : endings) {
            if (ends_with(token, parsed_word.first)) {
                return parsed_word.second;
            }
        }
        return {PartOfSpeech::Unknown, Gender::Unknown};
	}

	void solve(std::istream& in, std::ostream& out) {
        std::string line;
        std::getline(in, line);

        std::vector<std::string> tokens = {""};
        for (const char ch : line) {
            if (ch == ' ') {
                tokens.emplace_back("");
            } else {
                tokens.back() += ch;
            }
        }
        std::vector<ParsedWord> words;
        for (const auto& token : tokens) {
            words.emplace_back(parse(token));
        }

        const int n = words.size();
        const int count_masculine = std::count_if(all(words), [](const ParsedWord& word) {
            return word.second == Gender::Masculine;
        });
        const int count_feminine = std::count_if(all(words), [](const ParsedWord& word) {
            return word.second == Gender::Feminine;
        });
        const int count_nouns = std::count_if(all(words), [](const ParsedWord& word) {
            return word.first == PartOfSpeech::Noun;
        });
        const bool ordered = std::is_sorted(all(words), [](const ParsedWord& lhs, const ParsedWord& rhs) {
            return lhs.first < rhs.first;
        });

        const bool failed = (count_masculine != n && count_feminine != n || n > 1 && count_nouns != 1 || !ordered);
        out << (!failed ? "YES" : "NO") << std::endl;
	}


	AUrokiGrammatiki() {
        endings = {
                {"lios", {PartOfSpeech::Adjective, Gender::Masculine}},
                {"liala", {PartOfSpeech::Adjective, Gender::Feminine}},
                {"etr", {PartOfSpeech::Noun, Gender::Masculine}},
                {"etra", {PartOfSpeech::Noun, Gender::Feminine}},
                {"initis", {PartOfSpeech::Verb, Gender::Masculine}},
                {"inites", {PartOfSpeech::Verb, Gender::Feminine}}
        };
    }


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

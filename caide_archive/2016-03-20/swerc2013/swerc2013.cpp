#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 22;
const int MAXM = 22222;

set<string> asked_words;
set<std::vector<std::string>> asked_sentences;

inline void what_the_word(const std::string& word) {
	io << "What does the word \"" << word.c_str() << "\" mean?" << std::endl;
}

inline void what_the_sentence(const std::vector<std::string>& sentence) {
	if (sentence.size() == 1) {
		return;
	}
	io << "What does the sentence \"";
	bool not_first = false;
	for (const auto& it : sentence) {
		if (not_first) {
			io << ' ';
		}
		else {
			not_first = true;
		}
		io << it.c_str();
	}
	io << "\" mean?" << std::endl;
}

inline bool is_star(const char * s) {
	return s[0] == '*';
}

inline bool is_sharp(const char * s) {
	return s[0] == '#';
}

inline bool is_separator(const char * s) {
	return s[0] == '.' || s[0] == ',' || s[0] == ':' || s[0] == ';' || s[0] == '?' || s[0] == '!';
}

class Joe {
public:

	Joe(const size_t brain_size) : brain_size_(brain_size) {
		get_id("Joe", true);
	}

	void learn(const std::vector<std::string>& sentence) {
		std::vector<int> words = convert_to_words(sentence, true);
		std::set<std::vector<int>> subseq = get_subsequences(words);
		subsequences_.insert(subseq.begin(), subseq.end());
	}

	void test(const std::vector<std::string>& sentence) {
		std::vector<int> words = convert_to_words(sentence, false);
		std::set<std::vector<int>> subseq = get_subsequences(words);
		for (const auto& it : subseq) {
			if (subsequences_.count(it) == 0) {
				what_the_sentence(sentence);
				break;
			}
		}
		subsequences_.insert(subseq.begin(), subseq.end());
	}

private:
	set<vector<int>> subsequences_;
	map<string, int> str_;
	size_t brain_size_;

	int get_id(const std::string& s, bool add) {
		std::string word = lowerCase(s);
		if (str_.count(word)) {
			return str_[word];
		}
		if (!add) {
			what_the_word(s);
		}
		return str_[word] = str_.size();
	}

	std::vector<int> convert_to_words(const std::vector<std::string>& sentence, bool learn) {
		std::vector<int> result;
		result.reserve(sentence.size());
		for (const auto& it : sentence) {
			int id = get_id(it, learn);
			result.emplace_back(id);
		}
		return result;
	}

	std::set<std::vector<int>> get_subsequences(const std::vector<int>& words) const {
		std::set<std::vector<int>> result;
		for (size_t i = 0; i < words.size(); ++i) {
			std::vector<int> subseq;
			subseq.reserve(brain_size_);
			for (size_t j = i; j < std::min(words.size(), i + brain_size_); ++j) {
				subseq.emplace_back(words[j]);
				if (i != j) {
					result.insert(subseq);
				}
			}
		}
		return result;
	}


};

char s[MAXN];

void solve(istream& ins, ostream& out) {
	for (int _ = 1; !io.eof(); ++_) {
		io >> s;
		if (strlen(s) == 0) {
			break;
		}
		io << "Learning case " << _ << endl;
		int brain_size = atoi(s);
		Joe joe(brain_size);
		std::vector<std::string> sentence;
		for (;;) {
			io >> s;
			if (is_star(s)) {
				if (sentence.size() > 0) {
					joe.learn(sentence);
					sentence.clear();
				}
				break;
			}
			if (is_separator(s)) {
				joe.learn(sentence);
				sentence.clear();
				continue;
			}
			sentence.emplace_back(s);
		}
		assert(sentence.size() == 0);
		for (;;) {
			io >> s;
			if (is_sharp(s)) {
				if (sentence.size() > 0) {
					joe.test(sentence);
					sentence.clear();
				}
				break;
			}
			if (is_separator(s)) {
				joe.test(sentence);
				sentence.clear();
				continue;
			}
			sentence.emplace_back(s);
		}
		io << endl;
	}
}

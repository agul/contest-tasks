#pragma comment(linker, "/STACK:66777216")
#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <utility>
#include <functional>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <queue>
#include <cmath>
#include <random>
#include <sstream>
#include <numeric>
#include <limits>
#include <chrono>
#include <type_traits>
#pragma hdrstop

#ifdef _MSC_VER
#include <intrin.h>
#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif


namespace std {


}

#ifdef _MSC_VER

#endif


namespace Random {


}


inline char lowerCase(const char ch) {
	return (ch >= 'A' && ch <= 'Z') ? ch ^ 32 : ch;
}


inline std::string lowerCase(std::string s) {
	int n = s.length();
	for (int i = 0; i < n; ++i) {
		s[i] = lowerCase(s[i]);
	}
	return s;
}


class IO {
public:
	constexpr static const std::size_t kBufferSize = 1 << 18;

	IO() : read_bytes_count_(0), read_buffer_offset_(0), current_char_(0), eof_(false) {
		static_assert(kBufferSize > 32, "Size of a buffer must be greater than 32 due to comparison in IO::flush() method.");
	}

	~IO() {
		flush();
	}

	IO(const IO&) = delete;
	IO& operator=(const IO&) = delete;
	IO(const IO&&) = delete;
	IO& operator=(const IO&&) = delete;

	bool eof() const;

	inline void shift_char();
	inline void skipws();

	inline void next_string(char* s);

	IO& operator >>(char* s);

	inline void flush();
	inline void new_line();

	inline void print_int(const int32_t x);
	inline void print_char(const char ch);
	inline void print_string(const char* s);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const int32_t x);
	IO& operator <<(const char x);
	IO& operator <<(const char* s);

	// Intended to use with std::endl.
	IO& operator <<(std::ostream& (*)(std::ostream&));


private:
	using Buffer = std::array<char, kBufferSize>;
	Buffer read_buffer_;
	Buffer write_buffer_;
	std::size_t read_bytes_count_;
	std::size_t read_buffer_offset_;
	std::size_t write_buffer_offset_;
	bool eof_;
	char current_char_;

	inline void update_buffer();


	template<typename T>
	void print_number(const T& value);

};

extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;
extern IO io;


inline void next_string(char* s);

inline void new_line();

inline void print_int(const int32_t x);
inline void print_char(const char x);
inline void print_string(const char* s);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;

IO io;
const int MAXN = 22;


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
#include <fstream>


extern class IO io;
bool useFastIO = false;
istream * pin;
ostream * pout;

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;
    useFastIO = true;

    ostream& out = cout;
    out << fixed << setprecision(16);
    pin = &in; pout = &out;
    solve(in, out);
    return 0;
}


bool IO::eof() const {
	if (useFastIO) {
		return eof_;
	}
	return pin->eof();
}

inline void IO::skipws() {
	while (!eof_ && (current_char_ == ' ' || current_char_ == '\n')) {
		shift_char();
	}
}


template<typename T>
void IO::print_number(const T& value) {
	T current_value = value;
	if (write_buffer_offset_ + 32 > kBufferSize) {
		flush();
	}
	if (current_value < 0) {
		write_buffer_[write_buffer_offset_++] = '-';
		current_value = abs(current_value);
	} else
	if (current_value == 0) {
		write_buffer_[write_buffer_offset_++] = '0';
		return;
	}
	std::size_t start_index = write_buffer_offset_;
	while (current_value != 0) {
		write_buffer_[write_buffer_offset_++] = current_value % 10 + '0';
		current_value /= 10;
	}
	std::reverse(write_buffer_.begin() + start_index, write_buffer_.begin() + write_buffer_offset_);
}


inline void IO::update_buffer() {
	if (read_buffer_offset_ == read_bytes_count_) {
		read_bytes_count_ = fread(&read_buffer_[0], sizeof(read_buffer_[0]), read_buffer_.size(), stdin);
		if (read_bytes_count_ == 0) {
			eof_ = true;
			return;
		}
		read_buffer_offset_ = 0;
	}
}

inline void IO::shift_char() {
	update_buffer();
	current_char_ = read_buffer_[read_buffer_offset_++];
}


inline void IO::next_string(char* s) {
	if (current_char_ == '\0') {
		shift_char();
	}
	skipws();
	std::size_t index = 0;
	while (!eof_ && current_char_ != ' ' && current_char_ != '\n') {
		s[index++] = current_char_;
		shift_char();
	}
	s[index] = 0;
}


IO& IO::operator >>(char* s) {
	::next_string(s);
	return *this;
}


inline void IO::flush() {
	fwrite(&write_buffer_[0], sizeof(write_buffer_[0]), write_buffer_offset_, stdout);
	write_buffer_offset_ = 0;
}

inline void IO::new_line() {
	if (write_buffer_offset_ == kBufferSize) {
		flush();
	}
	write_buffer_[write_buffer_offset_++] = '\n';
}

inline void IO::print_int(const int32_t x) {
	print_number(x);
}


inline void IO::print_char(const char x) {
	if (write_buffer_offset_ == kBufferSize) {
		flush();
	}
	write_buffer_[write_buffer_offset_++] = x;
}

inline void IO::print_string(const char* s) {
	for (std::size_t i = 0; s[i] != '\0'; ++i) {
		if (write_buffer_offset_ == kBufferSize) {
			flush();
		}
		write_buffer_[write_buffer_offset_++] = s[i];
	}
}


IO& IO::operator <<(const int32_t x) {
	::print_int(x);
	return *this;
}


IO& IO::operator <<(const char x) {
	::print_char(x);
	return *this;
}

IO& IO::operator <<(const char* s) {
	::print_string(s);
	return *this;
}


IO& IO::operator <<(std::ostream& (*)(std::ostream&)) {
	::new_line();
	return *this;
}


inline void next_string(char* s) {
	if (useFastIO) {
		io.next_string(s);
		return;
	}
	*pin >> s;
}


inline void new_line() {
	if (useFastIO) {
		io.new_line();
		return;
	}
	*pout << std::endl;
}

inline void print_int(const int32_t x) {
	if (useFastIO) {
		io.print_int(x);
		return;
	}
	*pout << x;
}


inline void print_char(const char x) {
	if (useFastIO) {
		io.print_char(x);
		return;
	}
	*pout << x;
}

inline void print_string(const char* s) {
	if (useFastIO) {
		io.print_string(s);
		return;
	}
	*pout << s;
}
